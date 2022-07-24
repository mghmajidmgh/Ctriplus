 
#include "../headers/object.h"

namespace Ctriplus
{   
    object object::operator()(object argument){return func(argument); };    

    string object::toString(const string padding="")const{
        string ret=padding;
        string tpad="  ";

        if (type==OBJECT_TYPE::CHAR) {ret=to_string(value_char);}
        else if (type==OBJECT_TYPE::INT){ret=to_string(value_int);}
        else if (type==OBJECT_TYPE::LONG_LONG){ret=to_string(value_ll);}
        else if (type==OBJECT_TYPE::DOUBLE){ret=to_string(value_double);}
        else if (type==OBJECT_TYPE::LONG_DOUBLE){ret=to_string(value_long_double);}
        else if (type==OBJECT_TYPE::STRING){ret=(value_str);}
        else if (type==OBJECT_TYPE::ARRAY){
            bool isfirst=true;
            ret+="[";
            for(object const& item:*vec_ptr){
                if(isfirst){isfirst=false;}else{ret+=",";}
                ret+= item.toString();
            }
            ret+="]";
        }else if (type==OBJECT_TYPE::OBJECT){
             bool isfirst=true;
            ret+="\n"+padding+"{\n";
            for(auto& [key, value]: *map_ptr){
                if(isfirst){isfirst=false;}else{ret+=",\n";}
                ret+=padding+tpad+ key + ":" + value.toString(padding+tpad);
            }            
            ret+="\n"+padding+"}";
        }

        return ret;
    }

    std::ostream& operator<<(std::ostream& stream, const object& obj)
    {
        stream<<obj.toString("");
        return stream;
    }


    
string JSON::getWithoutWhiteSpace(string text){
    string ret="";
    for (size_t ind = 0; ind < text.length(); ind++)
    {        
        if (text[ind]=='"')
        {
            ret+=text[ind]; ind++;
             for (; ind < text.length(); ind++)  { ret+=text[ind];  if (text[ind]=='\\')  { ret+=text[ind+1]; ind+=2; } if(text[ind]=='\"')  { ind++; break;}  }         
        }
        char ch=text[ind];
        if (text[ind]!=' ' && text[ind]!='\n'  && text[ind]!='\t'){
            ret+=text[ind];
        }        
    }
    return ret;
}
var JSON::parse(string text,int ind) {
        var ret;

         for (; ind < text.length(); ind++)    { 
           
            if (text[ind]=='{')
            {
                while(text[ind]!='}' && ind < text.length()){
                    string name="";
                    ind++;
                    while(text[ind]!=':' && ind < text.length() ){name+=text[ind]; ind++;}
                    cout<<" name:"<<name;
                    ind++;//pass :
                    cout<<"ind:"<<ind<<endl;
                    var value=JSONparse( text, ind);
                    ind=value["ind"];
                    ret["value"][name]=value["value"];
                    cout<<"after call JSONparse, ind:"<<ind<<" value:"<<ret["value"][name]<<endl;
                    char tc=text[ind];
                    int t=0;
                    //ind++;//pass ,
                }
                ind++;//pass }
                ret["ind"]=ind;
                break;
            }else if (text[ind]=='[') {
                do{
                    ind++;
                    cout<<"in array,";
                    cout<<"ind:"<<ind<<endl;
                    var value=JSONparse( text, ind);
                    ret["value"].push_back( value["value"]);
                    ind=value["ind"];
                    cout<<"in array after call JSONparse, ind:"<<ind<<" value:"<<value["value"]<<endl;
                    char tc=text[ind];
                    int t=0;
                }while(text[ind]!=']' && ind < text.length());
                ret["ind"]=ind+1;
                break;
            }else{
                string value="";      
                bool isString=(text[ind]=='\"');         
               do{value+=text[ind]; ind++;}while( ( isString && text[ind]!='\"' || !isString && text[ind]!=':' && text[ind]!=',' && text[ind]!=']' && text[ind]!='}') && ind < text.length());
               if(isString){value+='\"';ind++;}
               ret["ind"]=ind;
               ret["value"]=value;
               break;
            }
            
         }

   return ret;
    }


}