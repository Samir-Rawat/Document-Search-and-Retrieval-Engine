#ifndef SEARCHWINDOW_HPP
#define SEARCHWINDOW_HPP

#include <QMainWindow>
#include <QComboBox>

#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "SearchEngine.hpp"
#include "ResultRanker.hpp"

class QLineEdit;
class QPushButton;
class QListWidget;

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

    signals:
        void searchRequested(const QString& query);


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

    InvertedIndex m_index;
    std::vector<Document> m_documents;

    SearchEngine searchEngine;
    RankingStrategy* rankingStrategy = nullptr;

    bool m_documentsLoaded = false;
};

#endif
