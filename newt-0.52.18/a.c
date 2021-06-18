#include <stdio.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#define MY_ENCODING "ISO-8859-1"

xmlNodePtr createRoot(xmlDocPtr doc, char* name)
{
    xmlNodePtr root;
    root = xmlNewNode(NULL, BAD_CAST name);
    xmlDocSetRootElement(doc, root);
    return root;
}

xmlNodePtr addChild(xmlNodePtr parent, char* name, char* value)
{
    return xmlNewChild(parent, NULL, BAD_CAST name, BAD_CAST value);
}

void setElementContent(xmlNodePtr element, char* value)
{
    xmlNodePtr it = NULL;
    int bFound = 0;

    for (it = element->children; it != NULL; it = it->next)
    {
        if (it->type == XML_TEXT_NODE)
        {
            xmlNodeSetContent(it, BAD_CAST value);
            bFound = 1;
        }
    }

    if (!bFound)
    {
        xmlNodeSetContent(element, BAD_CAST value);
    }
}

void setElementAttribute(xmlNodePtr element, char* attribName, char* attribValue)
{
    xmlSetProp(element, BAD_CAST attribName, BAD_CAST attribValue);
}

void printXml(xmlDocPtr doc)
{
    xmlChar* xmlbuff;
    int buffersize;

    //xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
    xmlDocDumpFormatMemoryEnc(doc, &xmlbuff, &buffersize, MY_ENCODING, 1);
    printf("%s", (char *) xmlbuff);
    xmlCleanupParser();
    xmlFree(xmlbuff);
}

int main(int argc, char** argv)
{
    xmlDocPtr  doc   = NULL;
    xmlNodePtr root  = NULL;
    xmlNodePtr tmp1  = NULL;
    xmlNodePtr tmp11 = NULL;
    xmlNodePtr tmp2  = NULL;
    xmlNodePtr tmp3  = NULL;
    xmlNodePtr tmp4  = NULL;
    xmlNodePtr it    = NULL;

    doc = xmlNewDoc(BAD_CAST "1.0");

    root = createRoot(doc, "root");

    // tmp1 = addChild(root, "child1", NULL);
    tmp1 = addChild(root, "child1", "OLD CONTENT");

    tmp11 = addChild(tmp1, "child1.1", NULL);
    setElementContent(tmp11, "blablabla");

    tmp2 = addChild(root, "child2", NULL);
    setElementContent(tmp2, "22222");
    setElementAttribute(tmp2, "id", "002");
    setElementAttribute(tmp2, "lang", "en");


    tmp3 = addChild(root, "child3", NULL); /* create empty */
    tmp4 = addChild(root, "cliente", NULL); /* create empty */

    
    printf("\nBefore:\n");
    printXml(doc);

    setElementContent(tmp1, "NEW CONTENT");
    setElementContent(tmp3, "333");
    setElementContent(tmp4, "NOVO CLIENTE");

    printf("\nAfter:\n");
    printXml(doc);

    xmlFreeDoc(doc);

    return 0;
}