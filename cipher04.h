/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H
#include <tuple>
#include <iostream>
using namespace std;

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
    virtual std::string getPseudoAuth() { return "Will Johnson"; }
    virtual std::string getCipherName() { return "Polybius Square Cipher"; }
    virtual std::string getEncryptAuth() { return "Will Johnson"; }
    virtual std::string getDecryptAuth() { return "Will Johnson"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string s;
        s += "crypto.interactive-maths.com (2013), ";
        s += "\"Polybius-Square Cipher\", \n   retrieved: ";
        s += "http://practicalcryptography.com/ciphers/classical-era/polybius-square/";
        return s;
    }

    /**********************************************************
     * GET PSEUDOCODE
     * Returns the pseudocode as a string to be used by the caller.
     **********************************************************/
    virtual std::string getPseudocode()
    {
        std::string str;

        // TODO: please format your pseudocode
        // The encrypt pseudocode
        str = "adjustedPlainText <- removeSpaces(plainText)\n";
        str += "key[5][5] <- GenerateKey(password)\n";
        str += "FOR i is all index of adjustedPlainText\n";
        str += "   coords = getCoords(adjustedPlainText[i], key);\n";
        str += "   switch(get<0>(coords))\n";
        str += "      CASE 0\n";
        str += "         cipherText += 'A'\n";
        str += "      CASE 1\n";
        str += "         cipherText += 'B'\n";
        str += "      CASE 2\n";
        str += "         cipherText += 'C'\n";
        str += "      CASE 3\n";
        str += "         cipherText += 'D'\n";
        str += "      CASE 4\n";
        str += "         cipherText += 'E'\n";
        str += "   switch(get<1>(coords))\n";
        str += "      CASE 0\n";
        str += "         cipherText += 'A'\n";
        str += "      CASE 1\n";
        str += "         cipherText += 'B'\n";
        str += "      CASE 2\n";
        str += "         cipherText += 'C'\n";
        str += "      CASE 3\n";
        str += "         cipherText += 'D'\n";
        str += "      CASE 4\n";
        str += "         cipherText += 'E'\n";
        str += "RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "key[5][5] <- GenerateKey(password)\n";
        str += "coords <- make_tuple(0, 0)\n";
        str += "FOR i is all index in cipherText\n";
        str += "   SWITCH (cipherText[i])\n";
        str += "      CASE 'A'\n";
        str += "         IF i is even\n";
        str += "            get<0>(coords) = 0\n";
        str += "         IF i is odd\n";
        str += "            get<1>(coords) = 0\n";
        str += "      CASE 'B'\n";
        str += "         IF i is even\n";
        str += "            get<0>(coords) = 1\n";
        str += "         IF i is odd\n";
        str += "            get<1>(coords) = 1\n";
        str += "      CASE 'C'\n";
        str += "         IF i is even\n";
        str += "            get<0>(coords) = 2\n";
        str += "         IF i is odd\n";
        str += "            get<1>(coords) = 2\n";
        str += "      CASE 'D'\n";
        str += "         IF i is even\n";
        str += "            get<0>(coords) = 3\n";
        str += "         IF i is odd\n";
        str += "            get<1>(coords) = 3\n";
        str += "      CASE 'E'\n";
        str += "         IF i is even\n";
        str += "            get<0>(coords) = 4\n";
        str += "         IF i is odd\n";
        str += "            get<1>(coords) = 4\n";
        str += "   IF i is odd\n";
        str += "      plainText += key[get<0>(coords)][get<1>(coords)]\n";
        str += "RETURN plainText\n\n";


        return str;
    }

    /**********************************************************
     * ENCRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {
        std::string cipherText;
        std::string adjustedPlainText = removeSpaces(plainText);
        char key[5][5];
        GenerateKey(password, key);
        for (int i = 0; i < adjustedPlainText.size(); i++)
        {
            auto coords = getCoords(adjustedPlainText[i], key);
            switch (get<0>(coords))
            {
            case 0:
                cipherText += 'A';
                break;
            case 1:
                cipherText += 'B';
                break;
            case 2:
                cipherText += 'C';
                break;
            case 3:
                cipherText += 'D';
                break;
            case 4:
                cipherText += 'E';
                break;
            }
            switch (get<1>(coords))
            {
            case 0:
                cipherText += 'A';
                break;
            case 1:
                cipherText += 'B';
                break;
            case 2:
                cipherText += 'C';
                break;
            case 3:
                cipherText += 'D';
                break;
            case 4:
                cipherText += 'E';
                break;
            }
        }

        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText;
        char key[5][5];
        GenerateKey(password, key);
        auto coords = std::make_tuple(0, 0);
        for (int i = 0; i < cipherText.size(); i++)
        {
            switch (cipherText[i])
            {
            case 'A':
                if (i % 2 == 0)
                    get<0>(coords) = 0;
                else
                    get<1>(coords) = 0;
                break;
            case 'B':
                if (i % 2 == 0)
                    get<0>(coords) = 1;
                else
                    get<1>(coords) = 1;
                break;
            case 'C':
                if (i % 2 == 0)
                    get<0>(coords) = 2;
                else
                    get<1>(coords) = 2;
                break;
            case 'D':
                if (i % 2 == 0)
                    get<0>(coords) = 3;
                else
                    get<1>(coords) = 3;
                break;
            case 'E':
                if (i % 2 == 0)
                    get<0>(coords) = 4;
                else
                    get<1>(coords) = 4;
                break;
            }
            if (i % 2 == 1)
                plainText += key[get<0>(coords)][get<1>(coords)];
        }

        return plainText;
    }
private:
    /*********************************************************
    * remove duplicates
    * goes through a string and removes duplicate values
    *********************************************************/
    std::string removeDuplicate(std::string originalPassword, std::string password)

    {
        // Used as index in the modified string 
        int index = 0;
        char temp[25] = { '\0' };
        // Traverse through all characters 
        for (int i = 0; i < originalPassword.size(); i++) {

            // Check if str[i] is present before it   
            for (int j = i + 1; j < password.size() - 1; j++)
                if (originalPassword[i] == password[j])
                {
                    password.erase(j, 1);
                    break;
                }
        }
        return password;
    }

    /**********************************************************
    * Generate Key
    * generates the key to use in the encryption and decryption
    **********************************************************/
    void GenerateKey(std::string password, char key[][5])
    {
        std::string originalPassword = password;
        password += "abcdefghiklmnopqrstuvwxyz";
        std::string plain = removeDuplicate(originalPassword, password);
        int index = 0;
        for (int col = 0; col < 5; col++)
        {
            for (int row = 0; row < 5; row++)
            {
                key[col][row] = plain[index++];

            }
        }


    }

    std::tuple <int, int> getCoords(char letter, char key[][5])
    {
        auto coords = std::make_tuple(0, 0);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                if (letter == key[i][j])
                {
                    get<0>(coords) = i;
                    get<1>(coords) = j;
                }
        }

        return coords;
    }

    std::string removeSpaces(std::string plainText) {
        plainText.erase(std::remove(plainText.begin(), plainText.end(), ' '), plainText.end());
        return plainText;
    }
};

#endif // CIPHER04_H