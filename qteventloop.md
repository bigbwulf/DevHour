# Qt Framework

## Understanding Qt's Event Loop and Signals/Slots
* The event loop starts by calling the applications `exec()` function:
```C++
QCoreApplication app(argc, argv);
return app.exec();
```
* The loop continuously checks for events: ie user-input through keyboard/mouse, network input
* An event creates an instance of `QEvent` which dispatches to the top `QObject`'s `event()` function
* The top `QObject` may implement an event handler or pass it to any subset of its children
* Each sub `QObject` may consume the event without passing it to its children

![Qt for Beginners - Qt Wiki](https://qt-wiki-uploads.s3.amazonaws.com/images/4/4c/Beginner-Class-Hierarchy.jpg)
 * Example: 
	 * `QMouseEvent` arrives at `Qwidget`. It decides, based on coordinates of the mouse, that the event must be passed to `QPushButton`.  If `QPushButton` is disabled, it will simply consume the event. If enabled, it will emit its `clicked()` signal
 * Signals are broadcasts without specific targets to the framework. Slots (functions) are connected to the signal and executed in the same order they were connected to the signal (assuming both `connect()` and `QObjects` are on the same thread)
 * Note that `QCore`/`QGui``Application` `exit()` slot doesn't quit the application immediately. It tells the event loop to quit when control returns to the event loop
 * This is an example of pushing an event onto the event loop: a `Qt::QueuedConnection` 
 ```connect(A, &A::somethingChanged, B, &BhandleChange, Qt::DirectConnection)```
 * With a `Qt::DirectConnection)`, `B::handleChange()` will execute on `A`'s thread. If the function is on a seperate thread and not thread-safe, we're going to get some interesting bugs. If it is thread-safe and on a separate thread, we will not get the benefits (or drawbacks?) of multi-threading 
 * Conversely, `Qt::QueuedConnection` will enqueue the signal in `B`'s event loop. When control returns to the event loop, it will invoke the slot method. 

```C++
#include <QDebug> 
#include <QCoreApplication>
#include <QObject>
#include <QTimer> 
class Foo : public QObject
{
    Q_OBJECT

    public:
    Foo( QObject* parent = 0 ) : QObject( parent )
    {}

    private:
    void doStuff()
    {
        qDebug() << "Emit signal one";
        emit signal1();

        qDebug() << "Emit finished";
        emit finished();

        qDebug() << "Emit signal two";
        emit signal2();
    }

    signals:
    void signal1();
    void signal2();

    void finished();

    public slots:
    void slot1()
    {
        qDebug() << "Execute slot one";
    }

    void slot2()
    {
        qDebug() << "Execute slot two";
    }

    void start()
    {
        doStuff();

        qDebug() << "Bye!";
    }
};

int main( int argc, char** argv )
{
    QCoreApplication app( argc, argv );

    Foo foo;

    QObject::connect( &foo, &Foo::signal1, &foo, &Foo::slot1 );
    QObject::connect( &foo, &Foo::signal2, &foo, &Foo::slot2 );

    QObject::connect( &foo, &Foo::finished, &app, &QCoreApplication::quit );

    QTimer::singleShot( 0, &foo, &Foo::start );
    return app.exec();
}

#include "main.moc"
```
#### Source
[Understanding Qt's Event Loop and Signals/Slots - deKonvoluted](https://dekonvoluted.github.io/programming/2018/09/16/qt-event-loop.html)
