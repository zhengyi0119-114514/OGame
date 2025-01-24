#include <exception>
#include <stdint.h>
#include <stddef.h>
#include <string_view>
#include <string>
#pragma once

#ifndef OGAME_HEAD_DEFINES
#define OGAME_HEAD_DEFINES

#ifdef _WIN32
    #define OGAME_API_EXPORT __declspec(dllexport)
    #define OGAME_API_IMPORT __declspec(dllimport)
    #define OGAME_API_EXPORT_WIN32 OGAME_API_EXPORT
    #define OGAME_API_IMPORT_WIN32 OGAME_API_IMPORT
#else
    #define OGAME_API_EXPORT 
    #define OGAME_API_IMPORT extern
    #define OGAME_API_EXPORT_WIN32
    #define OGAME_API_IMPORT_WIN32
#endif

#ifdef OGAME_EXPORT
    #define OGAME_API OGAME_API_EXPORT
    #define OGAME_API_WIN32 OGAME_API_EXPORT_WIN32
#else
    #define OGAME_API OGAME_API_IMPORT
    #define OGAME_API_WIN32 OGAME_API_IMPORT_WIN32
#endif

#define ref_this (*this)
#define null NULL

typedef uint32_t OGAME_RESULT;
#define OGAME_RESULT_NO_ERROR               ((OGAME_RESULT)0x00000000)
#define OGAME_RESULT_ARGUEMENT_IS_NULL      ((OGAME_RESULT)0x00000001)
class OGameError : public virtual std::exception
{
  public:
    explicit OGameError(std::string_view sMessage,OGAME_RESULT uErrorCode);
    OGAME_RESULT ErrorCode() const;
    std::string GetMessage() const;
  private:
    OGAME_RESULT m_uErrorCode;
    std::string m_sErrorMessage;
};

#endif