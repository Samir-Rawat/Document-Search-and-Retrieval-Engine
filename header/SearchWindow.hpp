#ifndef SEARCHWINDOW_HPP
#define SEARCHWINDOW_HPP

#include <QMainWindow>

#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "SearchEngine.hpp"
#include "ResultRanker.hpp"
#include "Trie.hpp"

class QLineEdit;
class QPushButton;
class QListWidget;
class QComboBox;
class QCompleter;
class QStringListModel;

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

    signals:
        void searchRequested(const QString& query);

private slots:
    void browseDirectory();

private:
    void loadDocuments();
    void performSearch();

    QLineEdit *directoryInput;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *loadButton;
    QPushButton* browseButton;
    QListWidget *resultsList;
    QComboBox* rankingSelector;
    QCompleter* completer;
    QStringListModel* completionModel;

    InvertedIndex m_index;
    std::vector<Document> m_documents;
    Trie m_trie;
    bool m_documentsLoaded = false;

    SearchEngine searchEngine;
    RankingStrategy* rankingStrategy = nullptr;
    
    void changeRankingStrategy(int index);
    void updateSuggestions(const QString& text);
};

#endif
