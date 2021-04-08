#pragma once
#include <QToolButton>
#include <QEvent>

class QToolPushButton :
	public QToolButton
{
	Q_OBJECT
public:
	explicit QToolPushButton(QWidget *parent = nullptr);
	~QToolPushButton();
	void setChangeIcon(QString Icon1, QString Icon2, QSize size);
	void setIndex(int nIndex);
	void setIcon1();
	void setIcon2();
signals:
	void checkSignal(int nIndex);
protected:
	bool eventFilter(QObject *watched, QEvent *event);
private:
	QString m_Icon1;
	QString m_Icon2;
	QSize   m_size;
	int     m_nIndex;
};

