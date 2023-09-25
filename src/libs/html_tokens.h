#ifndef HTML_TOKENS_H_
#define HTML_TOKENS_H_

struct HTML_LUT {
    const int name;
    const char* value;
};

enum HTML_TOKENS {
    HTML_STARTER = 0,
    HTML_HYPERLINK,
    HTML_H1,
    HTML_H2,
    HTML_H3,
    HTML_H4,
    HTML_H5,
    HTML_H6,
    HTML_P,
    HTML_BLOCKQUOTE,
    HTML_UL,
    HTML_OL,
    HTML_LI,
    HTML_BR,
    HTML_IMAGE,
    HTML_BOLD,
    HTML_BOLD_ITALIC,
    HTML_ITALIC
};

// a lookup table for smot 2 HTML
const struct HTML_LUT LUT[] = { { HTML_STARTER, "" },
                                { HTML_HYPERLINK, "<a href=\"$2\">$1</a>" },
                                { HTML_H1, "<h1> $1 </h1>" },
                                { HTML_H2, "<h2> $1 </h2>" },
                                { HTML_H3, "<h3> $1 </h3>" },
                                { HTML_H4, "<h4> $1 </h4>" },
                                { HTML_H5, "<h5> $1 </h5>" },
                                { HTML_H6, "<h6> $1 </h6>" },
                                { HTML_P, "<p> $1 </p>" },
                                { HTML_BLOCKQUOTE, "<blockquote> $1 </blockquote>" },
                                { HTML_UL, "<ul> $1 </ul>" },
                                { HTML_OL, "<ol> $1 </ol>" },
                                { HTML_LI, "<li> $1 </li>" },
                                { HTML_BR, "<br>" },
                                { HTML_IMAGE, "<img src=\"$2\">" },
                                { HTML_BOLD, "<b>$1<b>" },
                                { HTML_BOLD_ITALIC, "<b><i>$1</i></b>" },
                                { HTML_ITALIC, "<i>$1</i>" } };

#endif
