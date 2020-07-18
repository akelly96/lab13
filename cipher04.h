/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H
#include <tuple>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
    virtual std::string getPseudoAuth() { return "Will Johnson"; }
    virtual std::string getCipherName() { return "playfair"; }
    virtual std::string getEncryptAuth() { return "Will Johnson"; }
    virtual std::string getDecryptAuth() { return "Will Johnson"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string cited;
        cited += "Practical Cryptography, ";
        cited += "http://practicalcryptography.com/ciphers/classical-era/playfair/, ";
        cited += "Follow the instructions under 'The Algorithm'";
        return cited;
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
        str = "encrypt(plaintext, password)";
        str += "useable = jToI(password)"; //convert j to i for cipher to work
        str += "key = generateKey(password)";
        str += "";

        // The decrypt pseudocode
        str += "insert the decryption pseudocode\n";


        //helper routine
        str += "";

        return str;
    }

    /**********************************************************
     * ENCRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {
        std::string plainConverted = plainText;
        plainConverted = jToI(plainConverted); //convert all js to is
        plainConverted = handleDoubles(plainConverted); //replace all doubles with x

        if (plainConverted.length() % 2 != 0)//make sure the plaintext has an even number of letters
            plainConverted += "x";           //ie hammer becomes hamxer

        std::string passwordConverted = password;
        passwordConverted = jToI(passwordConverted); //convert all js to is for password
        
        char** key = generateKey(passwordConverted); //generate the cipher key

        //std::string cipherText = plainConverted;

        //now to encrypt
        for (int i = 0; i < plainConverted.length(); i += 2)
        {
            //search the cipher for the next two letters' coordinates
            auto coords1 = getCoords(plainConverted[i], key);
            auto coords2 = getCoords(plainConverted[i+1], key);

            //if the letters aren't in the same row or column
            if (get<0>(coords1) != get<0>(coords2) && get<1>(coords1) != get<1>(coords2))
            {
                int temp = get<1>(coords1);
                get<1>(coords1) = get<1>(coords2);
                get<1>(coords2) = temp;

                plainConverted[i] = key[get<0>(coords1)][get<1>(coords1)];//change first letter
                plainConverted[i+1] = key[get<0>(coords2)][get<1>(coords2)];//change second letter
            }

            //if the letters are on the same row
            else if (get<0>(coords1) == get<0>(coords2))
            {
                //change first letter of the pair
                if (get<1>(coords1) != 4)
                    plainConverted[i] = key[get<0>(coords1)][get<1>(coords1) + 1];
                else
                    plainConverted[i] = key[get<0>(coords1)][0];

                //change second letter of the pair
                if (get<1>(coords2) != 4)
                    plainConverted[i+1] = key[get<0>(coords2)][get<1>(coords2) + 1];
                else
                    plainConverted[i+1] = key[get<0>(coords2)][0];
            }

            //if the letters are in the same column
            else if (get<1>(coords1) == get<1>(coords2))
            {
                //change first letter of the pair
                if (get<0>(coords1) != 4)
                    plainConverted[i] = key[get<0>(coords1) + 1][get<1>(coords1)];
                else
                    plainConverted[i] = key[0][get<0>(coords1)];

                //change second letter of the pair
                if (get<0>(coords2) != 4)
                    plainConverted[i+1] = key[get<0>(coords2) + 1][get<1>(coords2)];
                else
                    plainConverted[i+1] = key[0][get<0>(coords2)];
            }
        }

        std::string cipherText = plainConverted;

        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        //std::string cipherConverted = cipherText;
        //cipherConverted = jToI(cipherConverted); //convert all js to is
        //plainConverted = handleDoubles(plainConverted); //replace all doubles with x

        //if (plainConverted.length() % 2 != 0)//make sure the plaintext has an even number of letters
            //plainConverted += "x";           //ie hammer becomes hamxer

        std::string passwordConverted = password;
        passwordConverted = jToI(passwordConverted); //convert all js to is for password

        char** key = generateKey(passwordConverted); //generate the cipher key

        std::string plainText = cipherText;

        //now to decrypt
        for (int i = 0; i < cipherText.length(); i += 2)
        {
            //search the cipher for the next two letters' coordinates
            auto coords1 = getCoords(plainText[i], key);
            auto coords2 = getCoords(plainText[i + 1], key);

            //if the letters aren't in the same row or column
            if (get<0>(coords1) != get<0>(coords2) && get<1>(coords1) != get<1>(coords2))
            {
                int temp = get<1>(coords1);
                get<1>(coords1) = get<1>(coords2);
                get<1>(coords2) = temp;

                plainText[i] = key[get<0>(coords1)][get<1>(coords1)];//change first letter
                plainText[i + 1] = key[get<0>(coords2)][get<1>(coords2)];//change second letter
            }

            //if the letters are on the same row
            else if (get<0>(coords1) == get<0>(coords2))
            {
                //change first letter of the pair
                if (get<1>(coords1) != 0)
                    plainText[i] = key[get<0>(coords1)][get<1>(coords1) - 1];
                else
                    plainText[i] = key[get<0>(coords1)][4];

                //change second letter of the pair
                if (get<1>(coords2) != 0)
                    plainText[i + 1] = key[get<0>(coords2)][get<1>(coords2) - 1];
                else
                    plainText[i + 1] = key[get<0>(coords2)][4];
            }

            //if the letters are in the same column
            else if (get<1>(coords1) == get<1>(coords2))
            {
                //change first letter of the pair
                if (get<0>(coords1) != 0)
                    plainText[i] = key[get<0>(coords1) - 1][get<1>(coords1)];
                else
                    plainText[i] = key[4][get<0>(coords1)];

                //change second letter of the pair
                if (get<0>(coords2) != 0)
                    plainText[i + 1] = key[get<0>(coords2) - 1][get<1>(coords2)];
                else
                    plainText[i + 1] = key[4][get<0>(coords2)];
            }
        }

        return plainText;
    }

    /**********************************************************
     * GENERATEKEY
     * TODO: generate the cipher's key based on the users
     * password
     **********************************************************/
    virtual char** generateKey(const std::string& password)
    {
        std::string alpha = "abcdefghiklmnopqrstuvwxyz";
        char** key = new char*[5];
        int row = 0;
        int col = 0;
        for (int i = 0; i < password.length(); i++)
        {
            std::size_t found = alpha.find_first_of(password[i]);
            if (found != std::string::npos)
                alpha.erase(found);//if password[i] was found, erase it

            else
                break;//if password[i] was not found, break the for loop and fill key with alpha

            key[row][col] = password[i];
            if (i % 4 != 0)
                col++;
            else
            {
                row++;
                col = 0;
            }
        }

        for (int i = 0; i < alpha.length(); i++)
        {
            key[row][col] = alpha[i];
            if (i % 4 != 0)
                col++;
            else
            {
                row++;
                col = 0;
            }
        }

        return key;
    }

    /**********************************************************
     * JTOI
     * Replaces all the Js with Is 
     **********************************************************/
    virtual std::string jToI(std::string& str)
    {
        /*for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == 'j')
                str[i] = 'i';
        }*/
        std::size_t found = str.find("j");
        while (found != std::string::npos)
        {
            str[found] = 'i';
            found = str.find("j");
        }
        return str;
    }

    /**********************************************************
     * HANDLEDOUBLES
     * Replace all repeat letters with an x
     **********************************************************/
    virtual std::string handleDoubles(std::string& str)
    {
        for (int i = 1; i < str.length(); i++)
        {
            if (str[i] == str[i - 1])
                str[i] = 'x';
        }
        
        return str;
    }

    /**********************************************************
     * SEARCHCIPHER
     * Find the coordinates of a given letter and return them.
     **********************************************************/
    virtual std::tuple <int, int> getCoords(char letter, char** &key)
    {
        auto coords = std::make_tuple(0, 0);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                if (letter == key[i][j])
                {
                    //coords[0] = i;
                    //coords[1] = j;
                    get<0>(coords) = i;
                    get<1>(coords) = j;
                }
        }

        return coords;
    }
};

#endif // CIPHER04_H