#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QSplitter>
#include <QJsonDocument>
#include <QJsonObject>

class KnowledgeBase : public QWidget
{
    Q_OBJECT

public:
    explicit KnowledgeBase(QWidget *parent = nullptr);

private slots:
    void onTopicSelected(int currentRow);

private:
    void setupUI();
    void loadKnowledgeData();
    void populateTopicList();
    void displayTopicContent(const QString &topic);
    
    QSplitter *mainSplitter;
    QListWidget *topicList;
    QTextEdit *contentArea;
    QLabel *titleLabel;
    
    QJsonObject knowledgeData;
    QStringList topicKeys;
};

#endif // KNOWLEDGEBASE_H