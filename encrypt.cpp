#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "xCipher_utils.h"

using namespace std;

void print_matrix(const vector<vector<uint8_t> > &matrix)
{
	for (const auto &row : matrix)
	{
		for (const auto &byte : row)
		{
			cout << hex << setw(2) << setfill('0') << static_cast<int>(byte) << " ";
		}
		cout << endl;
	}
}


int main()
{

	string text;
	string key;
	string ciphertext = "";
	string plaintext = "";
	string outputtext = "";
	vector<vector<vector<uint8_t> > > matrixKey(6, vector<vector<uint8_t> >(4, vector<uint8_t>(4, 0x00)));
	cout << "Enter message:" << endl;
	getline(cin, text);
	cout << "Enter key (hex, 32 chars):" << endl;
	getline(cin, key);
	cout << endl;
	if (key.size() != 32)
	{
		cout << "Key must be 32 characters" << endl;
		return 0;
	}
	vector<uint8_t> textInHEX(text.begin(), text.end());

	for (int i = 0, forMatrix = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++, forMatrix += 2)
		{
			string byte_string = key.substr(forMatrix, 2);
			uint8_t byte = static_cast<uint8_t>(stoi(byte_string, nullptr, 16));
			matrixKey[0][i][j] = byte;
		}
	}	
	matrixKey[1] = KeyExpansion(matrixKey[0]);
	matrixKey[2] = KeyExpansion(matrixKey[1]);
	matrixKey[3] = KeyExpansion(matrixKey[2]);
	matrixKey[4] = KeyExpansion(matrixKey[3]);
	matrixKey[5] = KeyExpansion(matrixKey[4]);
	for (int block = 0; block < textInHEX.size(); block += 16)
	{

		vector<vector<uint8_t> > matrix(4, vector<uint8_t>(4, 0x00));
		for (int u = block, i = 0, j = 0; u < textInHEX.size() && u < block + 16; u++)
		{
			if (j == 4)
			{
				i++;
				j = 0;
			}
			matrix[i][j] = textInHEX[u];
			j++;
		}

		int round = 5;
		while (round--)
		{
			vector<vector<uint8_t> > mixingConstants = {
				{0x02, 0x03, 0x01, 0x01},
				{0x01, 0x02, 0x03, 0x01},
				{0x01, 0x01, 0x02, 0x03},
				{0x03, 0x01, 0x01, 0x02}};

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					uint8_t shifted = ShiftBits(matrix[i][j], matrixKey[5 - round][i][j], (i * 4 + j) % 8);
					uint8_t subbed = SubBytes(shifted);
					matrix[i][j] = subbed;
				}
			}


			matrix = MixColumns(matrix, mixingConstants, matrixKey[5 - round]);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix[i][j] = matrix[i][j] ^ matrixKey[5 - round][i][j];
				}
			}
			matrix = SwapBytes(matrix, matrixKey[5 - round]);
		}
		stringstream ss;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ss << hex << setw(2) << setfill('0') << static_cast<int>(matrix[i][j]);
			}
		}
		ciphertext += ss.str();
	}
	cout << "Your ciphertext is " << ciphertext << endl;
	cout << endl;

	return 0;
}