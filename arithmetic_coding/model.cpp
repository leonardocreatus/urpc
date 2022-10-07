#include "model.hpp"

/* THE BIT BUFFER */

static int buffer;
static int bits_to_go;
static int gargabe_bits;
static code_value value; /* Currently-seen code value */
static code_value low, high; 
std::stringstream out;
std::stringstream in;

static void bit_plus_follow(int bit); /* Routine that follows */

static long bits_to_follow; /* Number of opposite bits to output after the next bit */

int char_to_index[No_of_chars]; /* To index from character */
unsigned char index_to_char[No_of_symbols+1]; /* To character from index */

/* CUMULATIVE FREQUENCY TABLE */
int cum_freq[No_of_symbols+1]; /* Cumulative symbol frequencies */

int freq[No_of_symbols + 1];
/* INITIALIZE FOR BIT OUTPUT  */

void start_outputing_bits(){
    buffer = 0;
    bits_to_go = 8;
}

/*  OUTPUT A BIT  */

void output_bit(int bit)
{
    buffer >>= 1;
    if(bit) buffer |= 0x80;
    bits_to_go -= 1;
    if(bits_to_go == 0){
        // putc(buffer, stdout);
        out << (char)buffer;
        bits_to_go = 8;
    }
}

/* FLUSH OUT THE LAST BITS  */

std::string done_outputing_bits(){
    int temp = buffer >> bits_to_go;
    out << (char)temp;
    return out.str();

}

/* INITIALIZE BIT INPUT */

void start_inputing_bits(){
    bits_to_go = 0;
    gargabe_bits = 0;
}

/* INPUT A BIT */

int input_bit(){
    int t;
    if(bits_to_go == 0 ){
        // buffer = getc(stdin);
        buffer = in.get();
        if(buffer == EOF){
            gargabe_bits += 1;
            if(gargabe_bits > Code_value_bits - 2){
                fprintf(stderr, "Bad input file\n");
                exit(-1);
            }
        }
        bits_to_go = 8;
    }

    t = buffer & 1;
    buffer >>= 1;
    bits_to_go -= 1;
    return t;
    
}

/* START DECODING A STREAM OF SYMBOLS */ 

void start_decoding(std::string str){
    in.str(str);
    int i;
    value = 0;
    for(i = 1; i <= Code_value_bits; i++){
        value = 2*value + input_bit();
    }

    low = 0;
    high = Top_value;
}

/* DECODE THE NEXT SYMBOL */

int decode_symbol( int cum_freq[])
{
    int symbol; /* Return value */
    long range; /* Size of current code region */
    long cum; /* Cumulative frequency calculated */
//    int i; /* Counter for binary search */

    range = (long)(high-low)+1;
    cum = (((long)(value-low)+1)*cum_freq[0]-1)/range;
    for (symbol = 1; cum_freq[symbol] > cum; symbol++);
    high = low + (range*cum_freq[symbol-1])/cum_freq[0]-1;
    low = low + (range*cum_freq[symbol])/cum_freq[0];
    for(;;){
        if (high < Half){
            /* Nothing */
        } else if (low >= Half){
            value -= Half;
            low -= Half;
            high -= Half;
        } else if (low >= First_qtr && high < Third_qtr){
            value -= First_qtr;
            low -= First_qtr;
            high -= First_qtr;
        } else break;
        low = 2*low;
        high = 2*high+1;
        value = 2*value + input_bit();
    }
    return symbol;
}

/* START ENCODING A STREAM OF SYMBOLS */

void start_encoding()
{
    low = 0; 
    high = Top_value; 
    bits_to_follow = 0;
}

/* ENCODE A SYMBOL */

void encode_symbol( int symbol, int cum_freq[])
{
    long range; /* Size of the current code region */
    range = (long)(high-low)+1;
    high = low + (range*cum_freq[symbol-1])/cum_freq[0]-1;
    low = low + (range*cum_freq[symbol])/cum_freq[0];
    for(;;){
        if (high < Half){
            bit_plus_follow(0);
        } else if (low >= Half){
            bit_plus_follow(1);
            low -= Half;
            high -= Half;
        } else if (low >= First_qtr && high < Third_qtr){
            bits_to_follow += 1;
            low -= First_qtr;
            high -= First_qtr;
        } else break;
        low = 2*low;
        high = 2*high+1;
    }
}

/* FINISH ENCODING A STREAM OF SYMBOLS */

void done_encoding()
{
    bits_to_follow += 1;
    if (low < First_qtr) bit_plus_follow(0);
    else bit_plus_follow(1);
}

/* OUTPUT BITS PLUS FOLLOWING OPPOSITE BITS */

static void bit_plus_follow(int bit)
{
    output_bit(bit);
    while (bits_to_follow > 0){
        output_bit(!bit);
        bits_to_follow -= 1;
    }
}

/* INITIALIZE THE MODEL */

void start_model(){
    int i;
    for(i = 0; i < No_of_chars; i++){
        char_to_index[i] = i + 1;
        index_to_char[i + 1] = i;
    }

    for(i = 0; i <= No_of_symbols; i++){
        freq[i] = 1;
        cum_freq[i] = No_of_symbols - i;
    }
    freq[0] = 0;
}

/* UPDATE THE MODEL TO ACCOUNT FOR A NEW SYMBOL */

void update_model(int symbol)
{
    int i;
    if(cum_freq[0] == Max_frequency){
        int cum = 0;
        for(i = No_of_symbols; i >= 0; i--){
            freq[i] = (freq[i] + 1) / 2;
            cum_freq[i] = cum;
            cum += freq[i];
        }
    }
    for(i = symbol; freq[i] == freq[i - 1]; i--);
    if(i < symbol){
        int ch_i = index_to_char[i];
        int ch_symbol = index_to_char[symbol];
        index_to_char[i] = ch_symbol;
        index_to_char[symbol] = ch_i;
        char_to_index[ch_i] = symbol;
        char_to_index[ch_symbol] = i;
    }
    freq[i]++;
    while(i > 0){
        i--;
        cum_freq[i]++;
    }
}
