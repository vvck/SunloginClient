#include "QToolPushButton.h"
#include <QIcon>

QToolPushButton::QToolPushButton(QWidget *parent /*= nullptr*/) :
	QToolButton(parent), m_nIndex(-1)
{
	this->installEventFilter(this);
    this->setCheckable(true);

	connect(this, &QToolPushButton::clicked, [=](bool bCheck) {
		if (bCheck)
		{
			this->setIcon2();
			emit this->checkSignal(m_nIndex);
		}
		else
		{
			this->setChecked(true);
		}
	});
}

QToolPushButton::~QToolPushButton()
{

}

void QToolPushButton::setChangeIcon(QString Icon1, QString Icon2, QSize size)
{
	m_Icon1 = Icon1;
	m_Icon2 = Icon2;
	m_size = size;
	this->setIcon(QIcon(m_Icon1));
	this->setIconSize(size);
}

void QToolPushButton::setIndex(int nIndex)
{
	m_nIndex = nIndex;
}

void QToolPushButton::setIcon1()
{
	if(!m_Icon1.isEmpty()) {
		this->setIcon(QIcon(m_Icon1));
		this->setIconSize(m_size);
	}
}

void QToolPushButton::setIcon2()
{
	if (!m_Icon2.isEmpty()) {
		this->setIcon(QIcon(m_Icon2));
		this->setIconSize(m_size);
	}
}

bool QToolPushButton::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == this)
	{
		if (!this->isChecked())
		{
			if (event->type() == QEvent::Enter && !m_Icon1.isEmpty()) {
				this->setIcon2();
			}
			else if (event->type() == QEvent::Leave && !m_Icon2.isEmpty()) {
				this->setIcon1();
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}
