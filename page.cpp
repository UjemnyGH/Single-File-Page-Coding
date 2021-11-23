#include "SFPG/pageCoding.hpp"

class Html : public HTML::HtmlC
{
public:
    virtual void Code() override;
};

int main()
{
    Html h;

    h.Run("index.html");

    return 0;
}

void Html::Code()
{
    HTML::startHtml("pl");
    
    HTML::startHead();
    
    HTML::meta(HTML::charset, "UTF-8");
    CSS::openCssFromFile("style.css");

    HTML::endHead();

    HTML::startBody();

    HTML::startDiv(HTML::idT, "container");
    HTML::endDiv();

    HTML::endBody();

    HTML::endHtml();
}