#ifndef SEARCHWINDOW_HPP
#define SEARCHWINDOW_HPP

#include <QMainWindow>
#include <QStringList>

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

    signals:
        void searchRequested(const QString& query);

private:
    void loadDocuments();
    void performSearch();

    QLineEdit *directoryInput;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *loadButton;
    QListWidget *resultsList;

    InvertedIndex m_index;
    SearchEngine searchEngine;
    std::vector<Document> documents;

    bool documentsLoaded = false;
};

#endif // SEARCHWINDOW_HPP
