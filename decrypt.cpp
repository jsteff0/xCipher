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

	string key;
	string ciphertext = "";
	string plaintext = "";
	vector<vector<vector<uint8_t> > > matrixKey(6, vector<vector<uint8_t> >(4, vector<uint8_t>(4, 0x00)));
	cout << "Enter your text" << endl;
	getline(cin, ciphertext);
	cout << "Enter your key in hex" << endl;
	getline(cin, key);
	cout << endl;
	if (key.size() != 32)
	{
		cout << "Key must be 32 characters" << endl;
		return 0;
	}

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

	for (int block = 0; block < ciphertext.size(); block += 32)
	{
		vector<vector<uint8_t> > matrix(4, vector<uint8_t>(4, 0x00));
		for (int u = block, i = 0, j = 0; u < ciphertext.size() && u < block + 32; u += 2)
		{
			if (j == 4)
			{
				i++;
				j = 0;
			}
			string byte_string = ciphertext.substr(u, 2);
			uint8_t byte = static_cast<uint8_t>(stoi(byte_string, nullptr, 16));
			matrix[i][j] = byte;
			j++;
		}

		int round = 5;
		while (round--)
		{
			vector<vector<uint8_t> > invMixingConstants = {
				{0x0e, 0x0b, 0x0d, 0x09},
				{0x09, 0x0e, 0x0b, 0x0d},
				{0x0d, 0x09, 0x0e, 0x0b},
				{0x0b, 0x0d, 0x09, 0x0e}};

			matrix = SwapBytes(matrix, matrixKey[round + 1], true);


			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix[i][j] = matrix[i][j] ^ matrixKey[round + 1][i][j];
				}
			}


			matrix = MixColumns(matrix, invMixingConstants, matrixKey[round + 1], true);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					uint8_t subbed = SubBytes(matrix[i][j], true);
					uint8_t shifted = ShiftBits(subbed, matrixKey[round + 1][i][j], (i * 4 + j) % 8, true);
					matrix[i][j] = shifted;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				plaintext += static_cast<char>(matrix[i][j]);
			}
		}
	}
	cout << "Your plaintext is " << plaintext << endl;
	cout << endl;

	return 0;
}