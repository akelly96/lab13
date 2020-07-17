/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H
#pragma warning(disable : 4996)

struct Index
{
    int col;
    int row;
};

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
    virtual std::string getPseudoAuth() { return "Ryan Blomquist"; }
    virtual std::string getCipherName() { return "Playfair Cipher"; }
    virtual std::string getEncryptAuth() { return "Austin Kelly"; }
    virtual std::string getDecryptAuth() { return "decrypt author"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        return std::string("citation");
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
        str = "key[6][6] <- GenerateKey(password)\n";
        str += "cipherText <- adjustText(plainText)\n";
        str += "for i < ciphertext.size i +=2\n";
        str += "   if Arow == Brow";
        str += "      digram.A = keyA[col][(row +1) % 6]\n";
        str += "      digram.B = keyB[col][(row +1) % 6]\n";
        str += "   else if Acol == Bcol";
        str += "      digram.A = keyA[(col +1) % 6][row]\n";
        str += "      digram.B = keyB[(col +1) % 6][row]\n";
        str += "   else\n";
        str += "      digram.A = keyB[col][keyA.row]\n";
        str += "      digram.B = keyA[col][keyB.row]\n";


        // The decrypt pseudocode
        str += "key[6][6] <- GenerateKey(password)";
        str += "for i < ciphertext.size i +=2\n";
        str += "   if Arow == Brow";
        str += "      digram.A = keyA[col][(row -1) % 6]\n";
        str += "      digram.B = keyB[col][(row -1) % 6]\n";
        str += "   else if Acol == Bcol";
        str += "      digram.A = keyA[(col -1) % 6][row]\n";
        str += "      digram.B = keyB[(col -1) % 6][row]\n";
        str += "   else\n";
        str += "      digram.A = keyB[col][keyA.row]\n";
        str += "      digram.B = keyA[col][keyB.row]\n";
        str += "plaintext <- adjustText(cipherText)\n";

        

        return str;
    }

    /**********************************************************
     * ENCRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {
        std::string cipherText = plainText;
        char key[6][6];
        GenerateKey(password, key);
        cipherText = alterCipher(cipherText, true);
        Index indexA;
        Index indexB;
        for (int i = 0; i < cipherText.size() - 1; i += 2)
        {
            indexA = getIndeces(key, cipherText[i]);
            indexB = getIndeces(key, cipherText[i + 1]);
            if (indexA.row == indexB.row)
            {
                cipherText[i] = key[indexA.row][(indexA.col + 1) % 6];
                cipherText[i + 1] = key[indexB.row][(indexB.col + 1) % 6];
            }
            else if (indexA.col == indexB.col)
            {
                cipherText[i] = key[(indexA.row + 1) % 6][indexA.col];
                cipherText[i + 1] = key[(indexB.row + 1) % 6][indexB.col];
            }
            else
            {
                cipherText[i] = key[indexA.row][indexB.col];
                cipherText[i + 1] = key[indexB.row][indexA.col];
            }
        }
        
        // TODO - Add your code here
        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText = cipherText;
        char key[6][6];
        GenerateKey(password, key);
        Index indexA;
        Index indexB;
        for (int i = 0; i < plainText.size(); i += 2)
        {
            indexA = getIndeces(key, plainText[i]);
            indexB = getIndeces(key, plainText[i + 1]);

            if (indexA.row == indexB.row)
            {
                if (indexA.col - 1 < 0)
                {
                    plainText[i] = key[indexA.row][4];
                }
                else
                {
                    plainText[i] = key[indexA.row][(indexA.col - 1)];
                }
                if (indexB.col - 1 < 0)
                {
                    plainText[i + 1] = key[indexB.row][4];
                }
                else
                {
                    plainText[i + 1] = key[indexB.row][(indexB.col - 1)];
                }
            }
            else if (indexA.col == indexB.col)
            {
                if (indexA.row - 1 < 0)
                {
                    plainText[i] = key[4][indexA.col];
                }
                else
                {
                    plainText[i] = key[(indexA.row - 1)][indexA.col];
                }
                if (indexB.row - 1 < 0)
                {
                    plainText[i + 1] = key[4][indexB.col];
                }
                else
                {
                    plainText[i + 1] = key[(indexB.row - 1)][indexB.col];
                }
            }
            else
            {
                plainText[i] = key[indexA.row][indexB.col];
                plainText[i + 1] = key[indexB.row][indexA.col];
            }
        }
        plainText = alterCipher(plainText, false);

        //this is the last step of the decryption.
        //does not bring back spaces
        plainText = alterCipher(plainText, false);
        // TODO - Add your code here
        return plainText;
    }
    /*********************************************************
    * remove duplicates
    * goes through a string and removes duplicate values
    *********************************************************/
    std::string removeDuplicate(char str[], int n)

    {
        // Used as index in the modified string 
        int index = 0;
        char temp[36] = { '\0' };
        // Traverse through all characters 
        for (int i = 0; i < n; i++) {

            // Check if str[i] is present before it   
            int j;
            for (j = 0; j < i; j++)
                if (str[i] == str[j])
                    break;

            // If not present, then add it to 
            // result. 
            if (j == i && index < 36)
                temp[index++] = str[i];
        }

        return (std::string)temp;
    }
    /**********************************************************
    * Generate Key
    * generates the key to use in the encryption and decryption
    **********************************************************/
    void GenerateKey(std::string password, char key[][6])
    {
        char pass[256];
        strcpy(pass, password.c_str());
        password += "abcdefghijklmnopqrstuvwxyz`~!@#$%^&*?";
        strcpy(pass, password.c_str());
        std::string plain = removeDuplicate(pass, password.size());

        int index = 0;
        for (int col = 0; col < 6; col++)
        {
            for (int row = 0; row < 6; row++)
            {
                key[col][row] = plain[index++];
                
            }
        }

        
    }
    /*****************************************************************
    * alterText
    * adjustst the cipher text to be able to run the text through
    * the cipher.
    * adjusts the cipher text to remove added letters to the plaintext
    ******************************************************************/
    std::string alterCipher(std::string cipherText, bool encrypt)
    {
        std::string text;
        cipherText.erase(remove_if(cipherText.begin(), cipherText.end(), isspace), cipherText.end());
        int len = cipherText.size();
        //when you are encrypting the text
        if (encrypt)
        {
            for (int i = 0; i < len; i++)
            {
                if (i > 0 && (cipherText[i] == cipherText[i - 1]))
                {
                    text += 'q';
                }
                text += cipherText[i];
            }
            if (text.size() % 2 != 0)
            {
                text += 'q';
            }
        } // when you are decrypting the text
        else
        {
            for (int i = 0; i < len; i++)
            {
                int index = cipherText.find('q', i);
                //check if the last character is a q
                if (i == len - 1 && cipherText[len - 1] == 'q')
                {
                    //if so do not add the q to the string
                }
                //check if the original string had two letters next to each other
                else if (i == index && cipherText[i - 1] == cipherText[i + 1])
                {
                    //if so do not add the middle value to the text
                }
                else
                {
                    text += cipherText[i];
                }
            }
        }
        return text;
    }

    Index getIndeces(char key[][6], char c)
    {
        Index index;
        for (index.row = 0; index.row < 6; index.row++)
        {

            for (index.col = 0; index.col < 6; index.col++)
            {
                if (key[index.row][index.col] == c) {
                    return index;
                }
            }
        }

    }
};

#endif // CIPHER02_H