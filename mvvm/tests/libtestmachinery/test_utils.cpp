//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/test_utils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "test_utils.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/serialization/jsonconverterinterfaces.h"
#include "mvvm/serialization/jsonutils.h"
#include "mvvm/utils/fileutils.h"
#include "testconfig.h" // this file is auto generated by the build system in build directory
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTextStream>
#include <stdexcept>
#include <string>

using namespace ModelView;

namespace {
void SaveDocument(const QJsonDocument& document, const std::string& fileName);
}

std::string TestUtils::TestOutputDir()
{
    return TestConfig::TestOutputDir(); // defined in auto-generated testconfig.h
}

std::string TestUtils::CreateTestDirectory(const std::string& test_sub_dir)
{
    std::string result = TestDirectoryPath(test_sub_dir);
    Utils::create_directory(result);
    return result;
}

std::string TestUtils::TestDirectoryPath(const std::string& test_sub_dir)
{
    return TestOutputDir() + std::string("/") + test_sub_dir;
}

std::string TestUtils::TestFileName(const std::string& test_sub_dir, const std::string& file_name)
{

    return TestDirectoryPath(test_sub_dir) + std::string("/") + file_name;
}

void TestUtils::SaveJson(const QJsonObject& object, const std::string& fileName)
{
    QJsonDocument document(object);
    SaveDocument(document, fileName);
}

void TestUtils::SaveJson(const QJsonArray& object, const std::string& fileName)
{
    QJsonDocument document(object);
    SaveDocument(document, fileName);
}

QString TestUtils::JsonToString(const QJsonObject& object)
{
    QJsonDocument document(object);
    return QString(document.toJson(QJsonDocument::Compact));
}

QString TestUtils::ModelToJsonString(SessionModel& model)
{
    return QString::fromStdString(JsonUtils::ModelToJsonString(model));
}

QJsonDocument TestUtils::LoadJson(const std::string& fileName)
{
    QFile jsonFile(QString::fromStdString(fileName));

    if (!jsonFile.open(QIODevice::ReadOnly))
        throw std::runtime_error("TestUtils::LoadJson() -> Can't read file");

    return QJsonDocument().fromJson(jsonFile.readAll());
}

std::string TestUtils::CreateTestFile(const std::string& dirname, const std::string& fileName)
{
    std::string filename = dirname.empty() ? fileName : dirname + "/" + fileName;

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("TestFileUtils::createTestFile() -> Error. "
                                 "Can't create file");

    QTextStream out(&file);
    out << "Test file " << 42 << "\n";
    file.close();

    return filename;
}

std::string TestUtils::CreateEmptyFile(const std::string& dirname, const std::string& fileName)
{
    std::string filename = dirname.empty() ? fileName : dirname + "/" + fileName;

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("TestFileUtils::createTestFile() -> Error. "
                                 "Can't create file");
    return filename;
}

namespace {

void SaveDocument(const QJsonDocument& document, const std::string& fileName)
{
    QFile saveFile(QString::fromStdString(fileName));

    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("TestUtils::SaveDocument() -> Can't save file");

    saveFile.write(document.toJson());
}

} // namespace
