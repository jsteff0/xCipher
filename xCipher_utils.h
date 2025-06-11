#ifndef XCIPHER_UTILS_H
#define XCIPHER_UTILS_H

#include <vector>
#include <cstdint>

using std::vector;

uint8_t gmul(uint8_t a, uint8_t b);
uint8_t ShiftBits(uint8_t byteinput, uint8_t keybyte, int shift, bool inv = false);
vector<vector<uint8_t> > ShiftColumns(vector<vector<uint8_t> > matrix, bool inv = false);
uint8_t SubBytes(uint8_t byte, bool inv = false);
vector<vector<uint8_t> > MixColumns(vector<vector<uint8_t> > &state, vector<vector<uint8_t> > &miningConstants, vector<vector<uint8_t> > &key, bool inv = false);
vector<vector<uint8_t> > KeyExpansion(vector<vector<uint8_t> > matrixKey);
vector<vector<uint8_t> > SwapBytes(vector<vector<uint8_t> > &state, vector<vector<uint8_t> > &key, bool inv = false);

extern vector<uint8_t> sbox;
extern vector<uint8_t> invSBox;
void print_matrix(const vector<vector<uint8_t> >& matrix);

#endif