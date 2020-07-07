#include "Tests/UnitTests/GUI/Comparators.h"
#include "Tests/UnitTests/utilities/google_test.h"
#include <QAbstractItemModel>
#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    Comparators::registerComparators();
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("LayoutChangeHint");
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");

    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
