#pragma once

#include <iostream>
#include <fstream>

std::string code = "\0";

namespace CSS
{
    void openCssFromFile(std::string file, bool putInCode = false) 
    {
        if(putInCode)
        {
            std::ifstream f(file, std::ios_base::binary);

            bool doRestCode = true;

            if(f.bad())
            {
                std::cout << "error: loading css from file\n";

                code += "<link rel=\"stylesheet\" href=\"" + file + "\">";

                doRestCode = false;
            }

            if(doRestCode)
            {
                f.seekg(0, std::ios_base::end);

                int len = static_cast<int>(f.tellg());

                f.seekg(0, std::ios_base::beg);

                std::string cssSrc;
                char *srcBuffer = new char[len + 1];
                f.read(srcBuffer, len);
                srcBuffer += '\0';
                f.close();

                cssSrc = srcBuffer;

                delete[] srcBuffer;

                code += "<style>\n" + cssSrc + "</style>\n";
            }
        }
        else
        {
            code += "<link rel=\"stylesheet\" href=\"" + file + "\">";
        }
    }
}

namespace HTML
{
    enum
    {
        charset,

        //

        classT,
        idT
    };

    void startHtml(std::string language) { code = "<!DOCTYPE HTML>\n<html lang=\"" + language + "\">\n"; }
    void endHtml() { code += "</html>\n"; }

    void startHead() { code += "<head>\n"; }
    void endHead() { code += "</head>\n"; }

    void startBody() { code += "<body>\n"; }
    void endBody() { code += "</body>\n"; }

    void addText(std::string text) { code += text; }

    void meta(uint32_t type, std::string value)
    {
        code += "<meta ";

        if(type == charset)
        {
            code += "charset=\"";
        }

        code += value + "\">\n";
    }

    void startDiv(unsigned int type = idT, std::string id = std::string("\0"))
    {
        if(type == idT)
        {
            code += "<div id=\"" + id + std::string("\">\n");
        }
        else if(type == classT)
        {
            code += "<div class=\"" + id + std::string("\">\n");
        }
    }

    void endDiv() { code += "</div>\n"; }

    void addCode(std::string additionalCode) { code += "<" + additionalCode + ">\n"; }

    class HtmlC
    {
    public:
        void Run(const char* htmlFileName) { Code(); std::ofstream f(htmlFileName, std::ios_base::out); f.write(code.data(), code.size()); f.close(); }
        virtual void Code() {}
    };
}