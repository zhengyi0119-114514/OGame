#pragma once
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>
#include "Base.hxx"
namespace OGame::Errors 
{
class OGameException : public virtual OGameObject
{
  public:
    virtual std::string ErrorMessage() const = 0;
    virtual std::string ToString() const = 0;
};
class FileNotFoundException : public virtual OGameException
{
  private:
    const std::string m_File;
  public:
    FileNotFoundException(std::filesystem::path file) : m_File(file.string()){}
    FileNotFoundException(std::string_view file) : m_File(file){}
    virtual std::string ErrorMessage() const override { return std::format("File {:} not found," , this->m_File); }
    virtual std::string ToString() const override {return this->ErrorMessage();};
    std::string GetFilePath() const { return this->m_File; }
};
class ArgumentIsNullException : public virtual OGameException
{
  private:
    std::string m_Argument;
  public:
    ArgumentIsNullException(std::string_view argument) : m_Argument(argument) {}
    virtual std::string ToString() const override {return std::format("{:} is null.",this->m_Argument);}
    virtual std::string ErrorMessage() const override {return this->ToString();};
    std::string GetArgumentName() const {return this->m_Argument;}
};
} // namespace OGame::Errors