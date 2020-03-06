#include<iostream>  
#include<string>  
#include<cmath>  
#include<algorithm>  
#include<list>  
#include<vector>  
#include<queue>  
using namespace std;  
list<string> text;  
list<string> cmd;  
void translate(string &str){  
    string::size_type position=0;  
    while((position=str.find("\\/",position))!=string::npos){  
        str.replace(position,2,"/");  
        position++;  
    }  
    return ;  
}  
void insertLine(int line,string &str){  
    //cout<<"Insert:"<<str<<" At:"<<line<<"\n"<<endl;  
    list<string>::iterator textItor=text.begin();  
    if(line>text.size())  
        textItor=text.end();  
    else  
        advance(textItor,line-1);  
    text.insert(textItor,str);  
    return ;  
}  
void replaceText(string &str,string &newStr){  
    //cout<<"Replace:"<<str<<" By:"<<newStr<<"\n"<<endl;  
    list<string>::iterator textItor=text.begin();  
    string::size_type position=0;  
    int strSize=str.size();  
    for(;textItor!=text.end();textItor++){  
        position=0;  
        while((position=textItor->find(str,position))!=string::npos){  
            textItor->replace(position,strSize,newStr);  
            position++;  
        }  
    }  
    return ;  
}  
bool deleteLine(int line){  
    if(line>text.size()){  
        //cout<<"No Line:"<<line<<" in this text!\n"<<endl;  
        return false;  
    }  
    //cout<<"Delete line at:"<<line<<"\n"<<endl;  
    list<string>::iterator textItor=text.begin();  
    advance(textItor,line-1);  
    text.erase(textItor);  
    /*for(textItor=text.begin();textItor!=text.end();textItor++) 
        cout<<*textItor<<"\n"; 
    cout<<endl;*/  
    return true;  
}  
void combineLine(int destLine,int sourceLine){  
    //cout<<"Combine line:"<<sourceLine<<" To:"<<destLine<<"\n"<<endl;  
    list<string>::iterator destItor=text.begin();  
    advance(destItor,destLine-1);  
    list<string>::iterator sourceItor=text.begin();  
    advance(sourceItor,sourceLine-1);  
    //cout<<"DestLine:"<<string(*destItor)<<" SourceLine:"<<string(*sourceItor)<<"\n"<<endl;  
    destItor->append(*sourceItor);  
    return ;  
}  
bool findText(int line,string &str){  
    //cout<<"Find text:"<<str<<" At:"<<line<<"\n"<<endl;  
    list<string>::iterator textItor=text.begin();  
    advance(textItor,line-1);  
    //cout<<"Find text:"<<str<<" At:"<<string(*textItor)<<"\n"<<endl;  
    if((textItor->find(str))!=string::npos){  
        //cout<<"Found!\n"<<endl;  
        return true;          
    }else{  
        //cout<<"Not found!\n"<<endl;  
        return false;  
    }  
}  
int main(){  
    //Define tmpstring and iterators for the input Text and Commands  
    string tmpStr;   
    list<string>::iterator textItor;  
    list<string>::iterator cmdItor;  
    //Define vector for "Find substring" command's answers  
    queue<bool> qAns;  
    //Input Text  
    while(getline(cin,tmpStr)){  
        if(tmpStr=="[Text]")  
            continue;  
        else if(tmpStr=="[/Text]")  
            break;  
        else{  
            text.push_back(tmpStr);  
        }  
    }  
    //Input Commands  
    while(getline(cin,tmpStr))  
        cmd.push_back(tmpStr);  
    //Analysis Commands   
    for(cmdItor=cmd.begin();cmdItor!=cmd.end();cmdItor++){  
        string tmpCmd=string(*cmdItor);  
        switch(tmpCmd[0]){  
            //Insert line command  
            case 'i':{  
                string str;  
                int line=0;  
                int i=2;  
                for(;i<tmpCmd.length();i++)  
                    if(tmpCmd[i]!='/')  
                        line=(line+(tmpCmd[i]-'0'))*10;  
                    else  
                        break;  
                str.assign(tmpCmd,i+1,tmpCmd.length());  
                translate(str);  
                insertLine(line/10,str);  
                break;  
            }  
            //Replace text command  
            case 'c':{  
                string oldStr,newStr;  
                for(int i=2;i<tmpCmd.length();i++)  
                    if(tmpCmd[i]=='/'&&tmpCmd[i-1]!='\\'){  
                        oldStr.assign(tmpCmd,2,i-2);  
                        translate(oldStr);  
                        newStr.assign(tmpCmd,i+1,tmpCmd.length());  
                        translate(newStr);  
                        replaceText(oldStr,newStr);  
                        break;  
                    }  
                break;  
            }  
            //Delete line command  
            case 'd':{  
                int line=0;  
                for(int i=2;i<tmpCmd.length();i++)  
                    if(tmpCmd[i]!='\0')  
                        line=(line+(tmpCmd[i]-'0'))*10;  
                    else  
                        break;  
                deleteLine(line/10);  
                break;  
            }  
            //Combine lines command  
            case 'f':{  
                queue<int> sourceLines;  
                priority_queue<int> sortLines;  
                int sourceLine=0;  
                int wei=0,textSize=text.size();  
                int i=tmpCmd.length()-1;  
                for(;i>1;i--)  
                    if(tmpCmd[i]=='/'){  
                        wei=0;  
                        break;  
                    }else{  
                        sourceLine=(tmpCmd[i]-'0')*pow(10,wei)+sourceLine;  
                        wei++;  
                    }  
                if(sourceLine<=textSize){  
                    sourceLines.push(sourceLine);  
                    sortLines.push(sourceLine);  
                }  
                sourceLine=0,wei=0;  
                for(i=i-1;i>0;i--)  
                    if(tmpCmd[i]=='/'||tmpCmd[i]==' '){  
                        if(tmpCmd[i]=='/'){  
                            if(sourceLine<=textSize){  
                                sourceLines.push(sourceLine);  
                                sortLines.push(sourceLine);  
                            }  
                        }else{  
                            if(sourceLine<=textSize){  
                                sourceLines.push(sourceLine);  
                            }  
                        }  
                        sourceLine=0,wei=0;  
                    }else{  
                        sourceLine=(tmpCmd[i]-'0')*pow(10,wei)+sourceLine;  
                        wei++;  
                    }  
                while(sourceLines.size()!=1){  
                    int tmpSourceLine=sourceLines.front();  
                    sourceLines.pop();  
                    int tmpDestLine=sourceLines.front();  
                    combineLine(tmpDestLine,tmpSourceLine);  
                }  
                while(!sortLines.empty()){  
                    deleteLine(sortLines.top());  
                    sortLines.pop();  
                }  
                break;  
            }  
            //Find substring command  
            case 'q':{  
                int line=0;  
                string str;  
                int i=3;  
                for(;i<tmpCmd.length();i++)  
                    if(tmpCmd[i]!='/')  
                        line=(line+(tmpCmd[i]-'0'))*10;  
                    else  
                        break;  
                str.assign(tmpCmd,i+1,tmpCmd.length());  
                translate(str);  
                qAns.push(findText(line/10,str));  
                break;  
            }  
        }  
    }  
    while(!text.empty()){  
        cout<<text.front()<<"\n";  
        text.pop_front();  
    }  
    while(!qAns.empty()){  
        if(qAns.front())  
            printf("Yes\n");  
        else  
            printf("No\n");  
        qAns.pop();  
    }  
    return 0;  
}  