#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

vector<uint8_t> sbox = {
	// 0     1    2     3     4    5    6    7    8    9    A    B    C    D    E    F
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16	// F
};

vector<uint8_t> invSBox = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

const uint8_t gmul(uint8_t a, uint8_t b)
{
	uint8_t p = 0;
	for (int i = 0; i < 8 && a; i++)
	{
		if (a & 1)
			p ^= b;
		bool hi_bit_set = b & 0x80;
		b <<= 1;
		if (hi_bit_set)
			b ^= 0x11b;
		a >>= 1;
	}
	return p;
}
uint8_t ShiftBits(uint8_t byteinput, uint8_t keybyte, int shift, bool inv = false)
{
	uint8_t newbyte;
	if (!inv)
	{
		if (keybyte % 2 == 0)
			newbyte = (byteinput << shift) | (byteinput >> (8 - shift));
		else
			newbyte = (byteinput >> shift) | (byteinput << (8 - shift));
	}
	else
	{
		if (keybyte % 2 == 0)
			newbyte = (byteinput >> shift) | (byteinput << (8 - shift));
		else
			newbyte = (byteinput << shift) | (byteinput >> (8 - shift));
	}
	return newbyte;
}
vector<vector<uint8_t>> ShiftColumns(vector<vector<uint8_t>> matrix, bool inv = false)
{
	if (!inv)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				swap(matrix[i][j], matrix[i][j + 1]);
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j > 0; j--)
			{
				swap(matrix[i][j], matrix[i][j - 1]);
			}
		}
	}

	return matrix;
}

uint8_t SubBytes(uint8_t byte, bool inv = false)
{
	if (!inv)
		return sbox[byte];
	else
		return invSBox[byte];
}
vector<vector<uint8_t>> MixColumns(vector<vector<uint8_t>> &state, vector<vector<uint8_t>> &miningConstants, vector<vector<uint8_t>> &key, bool inv = false)
{
	vector<vector<uint8_t>> temp(4, vector<uint8_t>(4, 0x00));
	if (inv)
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				state[i][j] = state[i][j] ^ key[i][3 - j];
	state = ShiftColumns(state, inv);
	for (int c = 0; c < 4; c++)
	{
		for (int i = 0; i < 4; i++)
		{
			temp[i][c] = gmul(state[0][c], miningConstants[i][0]) ^ gmul(state[1][c], miningConstants[i][1]) ^ gmul(state[2][c], miningConstants[i][2]) ^ gmul(state[3][c], miningConstants[i][3]);
		}
	}
	state = ShiftColumns(state, inv);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			state[i][j] = inv ? (temp[i][j]) : (temp[i][j] ^ key[i][3 - j]);
	return state;
}

vector<vector<uint8_t>> KeyExpansion(vector<vector<uint8_t>> matrixKey)
{
	swap(matrixKey[0][3], matrixKey[1][3]);
	swap(matrixKey[1][3], matrixKey[2][3]);
	swap(matrixKey[2][3], matrixKey[3][3]);
	matrixKey[0][0] = matrixKey[0][3] ^ matrixKey[0][0];
	matrixKey[1][0] = matrixKey[1][3] ^ matrixKey[1][0];
	matrixKey[2][0] = matrixKey[2][3] ^ matrixKey[2][0];
	matrixKey[3][0] = matrixKey[3][3] ^ matrixKey[3][0];

	matrixKey[0][1] = matrixKey[0][0] ^ SubBytes(matrixKey[0][0]);
	matrixKey[1][1] = matrixKey[1][0] ^ SubBytes(matrixKey[1][0]);
	matrixKey[2][1] = matrixKey[2][0] ^ SubBytes(matrixKey[2][0]);
	matrixKey[3][1] = matrixKey[3][0] ^ SubBytes(matrixKey[3][0]);

	matrixKey[0][2] = matrixKey[0][1] ^ SubBytes(matrixKey[0][1]);
	matrixKey[1][2] = matrixKey[1][1] ^ SubBytes(matrixKey[1][1]);
	matrixKey[2][2] = matrixKey[2][1] ^ SubBytes(matrixKey[2][1]);
	matrixKey[3][2] = matrixKey[3][1] ^ SubBytes(matrixKey[3][1]);

	matrixKey[0][3] = matrixKey[0][2] ^ (SubBytes(matrixKey[0][0]) ^ matrixKey[0][0]);
	matrixKey[1][3] = matrixKey[1][2] ^ (SubBytes(matrixKey[1][0]) ^ matrixKey[1][0]);
	matrixKey[2][3] = matrixKey[2][2] ^ (SubBytes(matrixKey[2][0]) ^ matrixKey[2][0]);
	matrixKey[3][3] = matrixKey[3][2] ^ (SubBytes(matrixKey[3][0]) ^ matrixKey[3][0]);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrixKey[i][j] = SubBytes(matrixKey[i][j]);
		}
	}
	return matrixKey;
}
void print_matrix(const vector<vector<uint8_t>> &matrix)
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
vector<vector<uint8_t>> SwapBytes(vector<vector<uint8_t>> &state, vector<vector<uint8_t>> &key, bool inv = false)
{
	if (!inv)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int firstIndex = (key[i][j] & 0xF0) >> 4;
				int secondIndex = key[i][j] & 0x0F;
				swap(state[firstIndex / 4][firstIndex % 4], state[secondIndex / 4][secondIndex % 4]);
			}
		}
	}
	else
	{
		for (int i = 3; i >= 0; i--)
		{
			for (int j = 3; j >= 0; j--)
			{
				int firstIndex = (key[i][j] & 0xF0) >> 4;
				int secondIndex = key[i][j] & 0x0F;
				swap(state[firstIndex / 4][firstIndex % 4], state[secondIndex / 4][secondIndex % 4]);
			}
		}
	}
	return state;
}
// a5 19 bf 8f
// 66 13 b7 b2
// 89 39 e6 d1
// 4c ff 24 70

// 8c 19 39 d1
// e6 b2 8f ff
// 13 4c bf 66
// 89 a5 24 70
int main()
{
	string text;
	string key;
	string ciphertext = "";
	string plaintext = "";
	string outputtext = "";
	vector<vector<vector<uint8_t>>> matrixKey(6, vector<vector<uint8_t>>(4, vector<uint8_t>(4, 0x00)));
	cout << "Enter your text" << endl;
	getline(cin, text);
	cout << "Enter your key in hex" << endl;
	getline(cin, key);
	cout << endl;
	if (key.size() != 32)
	{
		cout << "Key must be 32 characters" << endl;
		return 0;
	}
	vector<uint8_t> hextext(text.begin(), text.end());
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

	for (int block = 0; block < hextext.size(); block += 32)
	{
		vector<vector<uint8_t>> matrix(4, vector<uint8_t>(4, 0x00));
		for (int u = block, i = 0, j = 0; u < hextext.size() && u < block + 32; u++)
		{

			if (j == 4)
			{
				i++;
				j = 0;
			}
			matrix[i][j] = hextext[u];
			j++;
		}
		int round = 5;
		while (round--)
		{

			vector<vector<uint8_t>> mixingConstants = {
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

	for (int block = 0; block < ciphertext.size(); block += 32)
	{
		vector<vector<uint8_t>> matrix(4, vector<uint8_t>(4, 0x00));
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
			vector<vector<uint8_t>> invMixingConstants = {
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