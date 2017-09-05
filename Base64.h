#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>

namespace Base64
{
    std::string base64_encode(const std::string &);

    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64(std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(7, SALT3); // insert SALT3 in the 3rd position of s
        s += SALT1;
        s = base64_encode(s);
        s= s+ SALT2 + SALT3 + SALT1;
        s = base64_encode(s);
        s.insert(1, "L");
        s.insert(7, "M");

        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//the keyys specified are being used for keylogger

    std::string base64_encode(const std::string &s)
    {
        std::string ret;    
        int val = 0;        
        int bits = -6;  
        const auto
        const int b63 = 0x3F;
       
        for(auto &c : s)
        {
            val = (val << 8) + c; // similar to: val = val * 2^8;
            bits += 8;
            do 
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);  
                bits -= 6;
            }while(bits >= 0)   
        }

        if(bits > -6)   // so at least 1 character was inserted
        {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }

        while(ret.size() % 4)   // this is evaluated as a true (it's not 0) or false (it's 0)
        {
            ret.push_back('=');
        }

        return ret;
    }

}

#endif // BASE_64
