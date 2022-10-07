#include <stdio.h>
#include "coding.hpp"


std::string decode(std::string str) {
    start_model();
    start_inputing_bits();
    start_decoding(str);
    std::string out;

    for(;;){
        int ch; int symbol;
        symbol = decode_symbol(cum_freq);
        if (symbol == EOF_symbol) break;
        ch = index_to_char[symbol];
        // std::cout << ch;
        // putc(ch, stdout);
        out += ch;
        update_model(symbol);
    }

    // return "";
    return out;
}

std::string encode(std::string str){


    start_model();
    start_outputing_bits();
    start_encoding();

    
    for(auto i : str){
        int ch; int symbol;
        //ch = getc(std::cin);
        ch = i;
        
        if (ch == EOF) break;
        symbol = char_to_index[ch];
        encode_symbol(symbol, cum_freq);
        update_model(symbol);
    }

    encode_symbol(EOF_symbol, cum_freq);
    done_encoding();
    return done_outputing_bits();
}


