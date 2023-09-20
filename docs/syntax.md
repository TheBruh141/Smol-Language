# Smol Syntax

markdown part
---

``` md
# H1
## H2
### H3
#### H4
##### H5
###### H6

Bold **bold text**
Italic *italicized text*
Blockquote > blockquote
Ordered List 1. First item
2. Second item
3. Third item
Unordered List - First item

- Second item
- Third item
Code `code`
Horizontal Rule ---
Link [title](https://www.example.com)
Image ![alt text](image.jpg)

```

Custom Smol Syntax
---

```h
/* multi line comment */
// one line comment


[::] // general Smol syntax encapsulate for visual blocks
<::> // general Smol syntax encapsulate for semantic blocks
[::].{ // general Smol attribute syntax
    .style = { 
        // style goes in there
        color:blue;
        text-align:center;
    }
    .link = {
        // if pressed. User will go to link
    }

    .type = "Button" // you can change the type of element this is
    /*
    like:
    button, 
    TODO: Add more types    
    */
}

[:| text 1 :][:| text 2 :] // splits the page into 2 vertical segments

```

## linking a css or a js file to a Smol File

in Smol currently there are no ways to natively write css or js files so you must link it from another file. Smol is just a wrapper around normal HTML, JS, and CSS (just like markdown)

> Note there is no support for javascript for linking too :D

```c
[:-> link "path/to/file.js" as f :] // this is a link
```

you can encapsulate more than one file at once

```c
[: 
-> link "path/to/file.js" as f;
   link "another/path/to/file.css" as f2;
:] 
```

to use it you can just reference a style in that file

```c
[: 
-> link "path/to/styles.css" as stl;
:]

[:
This is a stylized text
:].{
    style = {
        sty::custom_font;
        // or
        styles::custom_font;
    }
}
```


### Semantic blocks
---
semantic blocks are an experimental feature of the lanugage but they are currently here for enabling logic operations in the language. 


```c

<:
// some js code here
:>.{
    language: "js", // this can be a any language but for now just js or css
}
```
