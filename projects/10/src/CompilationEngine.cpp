#include "CompilationEngine.h"
#include <string>
#include <tinyxml2.h>


namespace JackAnalyzer {

CompilationEngine::CompilationEngine(const std::filesystem::path& input_path, const std::filesystem::path& output_path) : tokenizer(input_path), output_file(fopen(output_path.c_str(), "w"))
{   
    
    //init output tree
    if (!output_file)
    {
		throw std::runtime_error("Can't initialize output file: " + output_path.string());
    }

    output_XML = new tinyxml2::XMLDocument(true, tinyxml2::PRESERVE_WHITESPACE);
    tinyxml2::XMLElement* root = output_XML->NewElement("class");
    output_XML->InsertFirstChild(root);
    current_output_element = root;
}

void CompilationEngine::compileClass()
{
    //'class' name '{' classVarDec* subroutineDec*'}'
    
    if(std::strcmp(current_input_element->Name(), "keyword") == 0 && std::strcmp(current_input_element->GetText(), "class") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("A class must be declared first.");
    }
    
    current_input_element = current_input_element->NextSiblingElement();
 
    if(std::strcmp(current_input_element->Name(), "identifier") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else
    {
        throw std::runtime_error("A class must have an identifier.");
    }

    current_input_element = current_input_element->NextSiblingElement();

    if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "{") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("A class body should start with '{'.");
    }
    
    current_input_element = current_input_element->NextSiblingElement();
    
    while (current_input_element->NextSibling() != nullptr)
    {
        if(std::strcmp(current_input_element->Name(), "keyword") == 0)
        {
            if(std::strcmp(current_input_element->Name(), "static") == 0 || std::strcmp(current_input_element->Name(), "field") == 0)
            {
                tinyxml2::XMLElement* c_var_node = output_XML->NewElement("classVarDec");
                current_output_element->InsertEndChild(c_var_node);
                current_output_element = c_var_node;
                compileClassVarDec();
                current_output_element = c_var_node->Parent()->ToElement();
            }
            else if(std::strcmp(current_input_element->Name(), "constructor") == 0 || std::strcmp(current_input_element->Name(), "method") == 0 || std::strcmp(current_input_element->Name(), "function") == 0)
            {
                tinyxml2::XMLElement* subroutine_node = output_XML->NewElement("subroutineDec");
                current_output_element = subroutine_node;
                compileSubroutine();
                current_output_element = subroutine_node->Parent()->ToElement();
            }
            else 
            {
                throw std::runtime_error("expected a method or a class variable.");
            }
        }
        else if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "}") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("unexpected token.");
        }
        
        current_input_element = current_input_element->NextSiblingElement();
    }   
}

void CompilationEngine::compileClassVarDec() 
{
    //(static | field) type name (, name)* ';'
    //modifier
    if(std::strcmp(current_input_element->Name(), "keyword") == 0)
    {
        if(std::strcmp(current_input_element->GetText(), "field") == 0 || std::strcmp(current_input_element->GetText(), "static") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("A class variable modifier be a field or static keyword");
        }
    }
    else 
    {
        throw std::runtime_error("A class variable must start with modifier");
    }

    current_input_element = current_input_element->NextSiblingElement();

    //'int' | 'char' | 'boolean' | className
    //type
    if(std::strcmp(current_input_element->Name(), "keyword") == 0) //basic type
    {
        if(std::strcmp(current_input_element->GetText(), "int") == 0 || std::strcmp(current_input_element->GetText(), "char") == 0 || std::strcmp(current_input_element->GetText(), "boolean") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            current_input_element = current_input_element->NextSiblingElement();
        
            if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            }
            else 
            {
                throw std::runtime_error("A variable identifier is missing.");
            }
        }
        else 
        {
            throw std::runtime_error("A class type has to be a basic type or a class type.");
        }
    }
    else if(std::strcmp(current_input_element->Name(), "identifier") == 0) //class type
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        current_input_element = current_input_element->NextSiblingElement();
        
        if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("A variable identifier is missing.");
        }
    }
    else 
    {
        throw std::runtime_error("A class variable must start with modifier");
    }

    current_input_element = current_input_element->NextSiblingElement();

    //names list
    while (current_input_element->NextSibling() != nullptr) 
    {
        if(std::strcmp(current_input_element->Name(), "identifier") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("Expected variable identifier.");
        }
        
        current_input_element = current_input_element->NextSiblingElement();

        if(std::strcmp(current_input_element->Name(), "symbol") == 0)
        {
            if(std::strcmp(current_input_element->GetText(), ",") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                continue;
            }
            else if(std::strcmp(current_input_element->GetText(), ";") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                break;
            }
            else 
            {
                throw std::runtime_error("Unexpectd token.");
            }
        }
        else 
        {
            throw std::runtime_error("Expected variable identifier.");
        }

    }
}

void CompilationEngine::compileSubroutine() 
{
    //(constructor | function | method) (void | type) name '('ParameterList')' SubroutineBody
    //declaration
    if(std::strcmp(current_input_element->Name(), "constructor") == 0 || std::strcmp(current_input_element->Name(), "method") == 0 || std::strcmp(current_input_element->Name(), "function") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("Expected a method decularation with: constructor, function, or method.");
    }

    current_input_element = current_input_element->NextSiblingElement();

    //return type
    if(std::strcmp(current_input_element->Name(), "keyword") == 0) //basic type
    {
        if(std::strcmp(current_input_element->GetText(), "int") == 0 || std::strcmp(current_input_element->GetText(), "char") == 0 || std::strcmp(current_input_element->GetText(), "boolean") == 0 || std::strcmp(current_input_element->GetText(), "void") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("A return type has to be a basic type, a class, or void.");
        }
    }
    else if(std::strcmp(current_input_element->Name(), "identifier") == 0) //class type
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("A class variable must have a return type");
    }

    current_input_element = current_input_element->NextSiblingElement();

    if(std::strcmp(current_input_element->Name(), "identifier") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("Expected subroutine identifier.");
    }

    current_input_element = current_input_element->NextSiblingElement();

    if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "(") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("Expected a parameter list starting with '('.");
    }

    current_input_element = current_input_element->NextSiblingElement();

    tinyxml2::XMLElement* param_l_node = output_XML->NewElement("parameterList");
    current_output_element = param_l_node;
    compileParameterList();
    current_output_element = param_l_node->Parent()->ToElement();

    if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), ")") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("Expected a parameter list to end with ')'.");
    }

    current_input_element = current_input_element->NextSiblingElement();

    if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "{") == 0)
    {
        tinyxml2::XMLElement* subroutine_b_node = output_XML->NewElement("subroutineBody");
        current_output_element = subroutine_b_node;
        compileSubroutineBody();
        current_output_element = subroutine_b_node->Parent()->ToElement();
        
    }
    else 
    {
        throw std::runtime_error("A subroutine body is expected.");
    }
}

void CompilationEngine::compileParameterList() 
{
    // type name, * between () if any
    while (current_input_element->NextSibling() != nullptr) 
    {
        //type
        current_input_element = current_input_element->NextSiblingElement();
        if(std::strcmp(current_input_element->Name(), "keyword") == 0) //basic type
        {
            if(std::strcmp(current_input_element->GetText(), "int") == 0 || std::strcmp(current_input_element->GetText(), "char") == 0 || 
               std::strcmp(current_input_element->GetText(), "boolean") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                current_input_element = current_input_element->NextSiblingElement();
            
                if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
                {
                    current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                }
                else 
                {
                    throw std::runtime_error("A variable identifier is missing.");
                }
            }
            else 
            {
                throw std::runtime_error("A class type has to be a basic type or a class type.");
            }
        }
        else if(std::strcmp(current_input_element->Name(), "identifier") == 0) //class type
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            current_input_element = current_input_element->NextSiblingElement();

            if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            }
            else 
            {
                throw std::runtime_error("A variable identifier is missing.");
            }
        }
        else if (std::strcmp(current_input_element->Name(), "symbol") == 0)
        {
            if(std::strcmp(current_input_element->GetText(), ",") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                continue;
            }
            else if (std::strcmp(current_input_element->GetText(), ")") == 0) 
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                return;
            }
            else 
            {
                throw std::runtime_error("Unexpected token in a parameter list: " + std::string(current_input_element->GetText()));
            }
        }
        else 
        {
            throw std::runtime_error("A parameter type has to be a basic type or a class type.");
        }
    }

}

void CompilationEngine::compileSubroutineBody() 
{
    //'{' varDec*  statments '}'

    if(std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "{") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("A subroutine body must start with '{'.");
    }


    while (current_input_element->NextSibling() != nullptr) 
    {
        current_input_element = current_input_element->NextSiblingElement();
        
        if(std::strcmp(current_input_element->Name(), "keyword") == 0)
        {
            if(std::strcmp(current_input_element->Name(), "var") == 0)
            {
                tinyxml2::XMLElement* var_node = output_XML->NewElement("varDec");
                current_output_element = var_node;
                compileVarDec();
                current_output_element = var_node->Parent()->ToElement();
            }
            else if (std::strcmp(current_input_element->Name(), "let") == 0 || std::strcmp(current_input_element->Name(), "if") == 0 || 
                     std::strcmp(current_input_element->Name(), "while") == 0 || std::strcmp(current_input_element->Name(), "do") == 0 || 
                     std::strcmp(current_input_element->Name(), "return") == 0) 
            {
                tinyxml2::XMLElement* statment_node = output_XML->NewElement("statements");
                current_output_element = statment_node;
                compileStatment();
                current_output_element = statment_node->Parent()->ToElement();
            }
            else 
            {
                throw std::runtime_error("Unexpected keyword token in the body of the subroutine body.");
            }
            
        }
        else if (std::strcmp(current_input_element->Name(), "symbol") == 0 && std::strcmp(current_input_element->GetText(), "}") == 0) 
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            break;
        }
        else
        {
            throw std::runtime_error("unexpected token in subroutine body");
        }
    }
}

void CompilationEngine::compileVarDec()
{
  // 'var' type name (',' other names)* ';'

    if(std::strcmp(current_input_element->Name(), "keyword") == 0 && std::strcmp(current_input_element->GetText(), "var") == 0)
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
    }
    else 
    {
        throw std::runtime_error("A variable must start with var modifier");
    }

    current_input_element = current_input_element->NextSiblingElement();

    //'int' | 'char' | 'boolean' | className
    //type
    if(std::strcmp(current_input_element->Name(), "keyword") == 0) //basic type
    {
        if(std::strcmp(current_input_element->GetText(), "int") == 0 || std::strcmp(current_input_element->GetText(), "char") == 0 || std::strcmp(current_input_element->GetText(), "boolean") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            current_input_element = current_input_element->NextSiblingElement();
        
            if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
            }
            else 
            {
                throw std::runtime_error("A variable identifier is missing.");
            }
        }
        else 
        {
            throw std::runtime_error("A class type has to be a basic type or a class type.");
        }
    }
    else if(std::strcmp(current_input_element->Name(), "identifier") == 0) //class type
    {
        current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        current_input_element = current_input_element->NextSiblingElement();
        
        if(std::strcmp(current_input_element->Name(), "identifier") == 0) 
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("A variable identifier is missing.");
        }
    }
    else 
    {
        throw std::runtime_error("A class variable must start with modifier");
    }

    current_input_element = current_input_element->NextSiblingElement();

    //names list
    while (current_input_element->NextSibling() != nullptr) 
    {
        if(std::strcmp(current_input_element->Name(), "identifier") == 0)
        {
            current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
        }
        else 
        {
            throw std::runtime_error("Expected variable identifier.");
        }
        
        current_input_element = current_input_element->NextSiblingElement();

        if(std::strcmp(current_input_element->Name(), "symbol") == 0)
        {
            if(std::strcmp(current_input_element->GetText(), ",") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                continue;
            }
            else if(std::strcmp(current_input_element->GetText(), ";") == 0)
            {
                current_output_element->InsertEndChild(current_input_element->ShallowClone(output_XML));
                break;
            }
            else 
            {
                throw std::runtime_error("Unexpectd token.");
            }
        }
        else 
        {
            throw std::runtime_error("Expected variable identifier.");
        }

    }
}

void CompilationEngine::compileStatment() 
{
    //can be let, if, while, do, return
    compileLet();
    compileIf();
    compileWhile();
    compileDo();
    compileReturn();
}

void CompilationEngine::compileLet() 
{
    //'let' name ('[' expresstion ']')? '=' expresstion ';' 
    
    
}

void CompilationEngine::compileIf() 
{
    //'if' '(' expresstion ')' '{' statments '}' ('else' '{' statments '}')?

    
}

void CompilationEngine::compileWhile() 
{
    //'while' '(' expresstion ')' '{' statments '}'

   
}

void CompilationEngine::compileDo() 
{
    //'do' call subroutine ';'

    
}

void CompilationEngine::compileReturn() 
{
    //'return' expresstion? ';'

    compileStatment();
}

void CompilationEngine::compileExpression() 
{
    //term (op term)*
    compileTerm();
}

void CompilationEngine::compileTerm() 
{
    //intConst | strConst | keywordConst | varName | varName | varName '[' exeression ']' | '(' exeression ')' | unaryOpTerm | subrutineCall
}

void CompilationEngine::compileExpressionList(int num) 
{
    //(expresstion(',' expresstion)*)?

    compileExpression();
}

CompilationEngine::~CompilationEngine() 
{
    output_XML->SaveFile(output_file);
    fflush(output_file);
    fclose(output_file);
}

} // namespace JackAnalyzer
