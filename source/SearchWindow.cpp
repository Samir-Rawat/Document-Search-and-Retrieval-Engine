#include "SearchWindow.hpp"
#include "ResultRanker.hpp"
#include "Tokenizer.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QCompleter>
#include <QStringListModel>
#include <QDebug>

#include <filesystem>
#include <string>
#include <stdexcept>

SearchWindow::SearchWindow(QWidget *parent)
    : QMainWindow(parent), searchEngine(m_documents, m_index)
{
    setWindowTitle("Document Search Engine");
    resize(800, 550);

    // Main window container
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // Title
    auto *title = new QLabel("Document Search Engine", centralWidget);
    title->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    // Direcroty Input
    directoryInput = new QLineEdit(centralWidget);
    directoryInput->setPlaceholderText("Enter document directory path...");

    browseButton = new QPushButton("Browse", centralWidget);
    loadButton = new QPushButton("Load Documents", centralWidget);

    // Search bar and button
    searchInput = new QLineEdit(centralWidget);
    searchInput->setPlaceholderText("Enter your search query...");

    completionModel = new QStringListModel(this);

    completer = new QCompleter(completionModel, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    searchInput->setCompleter(completer);

    searchButton = new QPushButton("Search", centralWidget);

    // Rank Strategy Selector
    rankingSelector = new QComboBox(this);

    rankingSelector->addItem("Frequency");
    rankingSelector->addItem("TF-IDF");

    rankingStrategy = new FrequencyRanker();

    auto *directoryLayout = new QHBoxLayout();
    directoryLayout->addWidget(directoryInput);
    directoryLayout->addWidget(browseButton);

    auto *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(rankingSelector);
    searchLayout->addWidget(searchButton);

    // Results area
    auto *resultsLabel = new QLabel("Search Results", centralWidget);
    resultsList = new QListWidget(centralWidget);

    resultsList->setStyleSheet(
        "QListWidget {"
        "  font-size: 14px;"
        "  padding: 5px;"
        "}"
    );

    // Layout
    mainLayout->addWidget(title);
    mainLayout->addWidget(new QLabel("Document Directory:", centralWidget));
    mainLayout->addLayout(directoryLayout);
    mainLayout->addWidget(loadButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultsLabel);
    mainLayout->addWidget(resultsList);

    setCentralWidget(centralWidget);

    // Load documents
    connect(loadButton, &QPushButton::clicked, this, &SearchWindow::loadDocuments);
    connect(browseButton, &QPushButton::clicked, this, &SearchWindow::browseDirectory);

    // Search button and Enter key
    connect(searchButton, &QPushButton::clicked, this,&SearchWindow::performSearch);
    connect(searchInput, &QLineEdit::returnPressed, searchButton, &QPushButton::click);
    connect(searchInput, &QLineEdit::textEdited, this, &SearchWindow::updateSuggestions);

    //Ranking strategy
    connect(rankingSelector, &QComboBox::currentIndexChanged, this, &SearchWindow::changeRankingStrategy);
}

SearchWindow::~SearchWindow() {
    delete rankingStrategy;
}

void SearchWindow::loadDocuments() {
    const std::string directory = directoryInput->text().trimmed().toStdString();
    resultsList->clear();
    m_documentsLoaded = false;

    try {
        //load the documents
        m_index.clear();
        m_trie.clear();
        m_documents = loadDirectory(directory);

        QString errors;

        //build the inverted index of documents
        for (const auto& document : m_documents) {
            try {
                m_index.insert(document);

                const auto tokens = Tokenizer::tokenize(document.getContent());

                for (const auto& token : tokens) {
                    if (!token.empty())
                        m_trie.insert(token);
                }
            }
            catch (const std::exception& e) {
                errors += QString::fromStdString(document.getTitle() + ": " + e.what()) + '\n';
            }
        }

        if (!errors.isEmpty()) {
            QMessageBox::warning(this,"Indexing Warnings",
                "Some documents could not be indexed:\n\n" + errors
            );
        }

        if (m_documents.empty()) {
            QMessageBox::information(this, "No Documents",
                "No files were found in this directory."
            );
            return;
        }

        m_documentsLoaded = true;

        QMessageBox::information(this, "Success",
            QString("%1 documents loaded successfully.").arg(m_documents.size())
        );
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Directory Error",
            QString::fromStdString(e.what())
        );
    }
}

void SearchWindow::performSearch() {
    if (!m_documentsLoaded) {
        QMessageBox::warning(this, "Documents Not Loaded",
            "Load a directory before searching."
        );
        return;
    }

    const std::string query = searchInput->text().trimmed().toStdString();

    if (query.empty())
        return;

    resultsList->clear();

    try {
        SearchResults results = searchEngine.search(query);
        results = rankingStrategy->rank(results);

        for (const auto& result : results) {
            if (result.documentID < 1 || result.documentID > m_documents.size()) {
                continue;
            }

            const auto& document = m_documents[result.documentID - 1];

            QString itemText;

            if (rankingSelector->currentIndex() == 0) {
                itemText = QString("%1  |  Frequency: %2")
                    .arg(QString::fromStdString(document.getTitle()))
                    .arg(result.frequency);
            }
            else {
                itemText = QString("%1  |  TF-IDF: %2")
                    .arg(QString::fromStdString(document.getTitle()))
                    .arg(result.score, 0, 'f', 4);
            }

            resultsList->addItem(itemText);
        }

        if (resultsList->count() == 0)
            resultsList->addItem("No results found.");
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Search Error",
            QString::fromStdString(e.what())
        );
    }
}


void SearchWindow::browseDirectory() {
    const QString directory = QFileDialog::getExistingDirectory(this,
        "Select Document Directory", directoryInput->text()
    );

    if (!directory.isEmpty())
        directoryInput->setText(directory);
}

void SearchWindow::changeRankingStrategy(int index) {
    delete rankingStrategy;

    if (index == 0)
        rankingStrategy = new FrequencyRanker();
    else
        rankingStrategy = new TFIDFRanker();
}

void SearchWindow::updateSuggestions(const QString& text) {
    const QString prefix = text.section(' ', -1);

    completer->setCompletionPrefix(prefix);

    const auto suggestions = m_trie.getSuggestions(prefix.toStdString());

    QStringList words;

    for (const auto& word : suggestions)
        words.append(QString::fromStdString(word));

    completionModel->setStringList(words);
    if (!words.isEmpty())
        completer->complete();
}
