#include "SearchWindow.hpp"
#include "SearchWindow.hpp"
#include "ResultRanker.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>

#include <filesystem>
#include <string>

SearchWindow::SearchWindow(QWidget *parent)
    : QMainWindow(parent), searchEngine(m_index)
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

    directoryInput = new QLineEdit(centralWidget);
    directoryInput->setPlaceholderText("Enter document directory path...");

    loadButton = new QPushButton("Load Documents", centralWidget);

    // Search bar and button
    searchInput = new QLineEdit(centralWidget);
    searchInput->setPlaceholderText("Enter your search query...");

    searchButton = new QPushButton("Search", centralWidget);

    auto *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchInput);
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
    mainLayout->addWidget(directoryInput);
    mainLayout->addWidget(loadButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultsLabel);
    mainLayout->addWidget(resultsList);

    setCentralWidget(centralWidget);

    // Load documents
    connect(loadButton, &QPushButton::clicked,
            this, &SearchWindow::loadDocuments);

    // Search button and Enter key
    connect(searchButton, &QPushButton::clicked, this,&SearchWindow::performSearch);

    connect(searchInput, &QLineEdit::returnPressed,
            searchButton, &QPushButton::click);
}

void SearchWindow::loadDocuments()
{
    if (documentsLoaded) {
        QMessageBox::information(
            this, "Already Loaded",
            "Documents have already been loaded. "
            "Restart the application to load another directory."
            );
        return;
    }

    const std::string directory =
        directoryInput->text().trimmed().toStdString();

    if (directory.empty() || !fs::is_directory(directory)) {
        QMessageBox::warning(
            this, "Invalid Directory",
            "Please enter a valid directory path."
            );
        return;
    }

    try {
        documents = Document::loadDirectory(directoryInput->text().trimmed().toStdString());

        for (const auto& document : documents) {
            m_index.insert(document);
        }

        if (documents.empty()) {
            QMessageBox::information(
                this, "No Documents",
                "No files were found in this directory."
                );
            return;
        }

        documentsLoaded = true;
        directoryInput->setEnabled(false);
        loadButton->setEnabled(false);

    }
    catch (const fs::filesystem_error& e) {
        QMessageBox::critical(
            this, "Directory Error",
            QString::fromStdString(e.what())
            );
    }
}

void SearchWindow::performSearch()
{
    if (!documentsLoaded) {
        QMessageBox::warning(
            this, "Documents Not Loaded",
            "Load a directory before searching."
            );
        return;
    }

    const std::string query =
        searchInput->text().trimmed().toStdString();

    if (query.empty())
        return;

    resultsList->clear();

    auto result = searchEngine.search(query);

    if (result == nullptr) {
        resultsList->addItem("No results found.");
        return;
    }

    ResultRanker resultRanker;
    const auto& rankedResults = resultRanker.rank(result);

    for (const auto& [docID, frequency] : rankedResults) {
        if (docID < 1 || static_cast<std::size_t>(docID) > documents.size()) {
            continue;
        }

        const auto& document = documents[docID - 1];

        const QString itemText =
            QString("%1  |  Frequency: %2")
                .arg(QString::fromStdString(document.getTitle()))
                .arg(frequency);

        resultsList->addItem(itemText);
    }

    if (resultsList->count() == 0)
        resultsList->addItem("No results found.");
}
