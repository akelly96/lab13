/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

/********************************************************************
 * STRUCT KEY
 * This struct is used to hold the two keys for the affine cipher
 *******************************************************************/
struct Key {
    int a;
    int b;
};

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
    Cipher01() {
        valueMinimum = ' ';
        valueMaximum = '~';
        sizeAlphabet = valueMaximum - valueMinimum + 1;
    }

    virtual std::string getPseudoAuth() { return "Austin Kelly"; }
    virtual std::string getCipherName() { return "Affine Cipher"; }
    virtual std::string getEncryptAuth() { return "Austin Kelly"; }
    virtual std::string getDecryptAuth() { return "Austin Kelly"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string s;
        s += "PracticalCryptography.com (2020), ";
        s += "\"Affine Cipher\", \n   retrieved: ";
        s += "http://practicalcryptography.com/ciphers/classical-era/affine/";
        return s;
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
        str = "encrypt(plainText, password)\n";
        str += "   key <- keysFromPassword(password)\n";
        str += "   FOR p is all values of plainText\n";
        str += "      index <- (indexFromCharacter(*p))\n";
        str += "      cipherText += characterFromIndex(((index * key.a) + key.b) % size)\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += "   key <- keysFromPassword(password)\n";
        str += "   FOR c is all values of cipherText\n";
        str += "      index <- (indexFromCharacter(*c))\n";
        str += "      p <- ((modInverse(key.a, size) * (index - key.b) % size) + size) % size\n";
        str += "      plainText += characterFromIndex(p)\n";
        str += "   RETURN plainText\n\n";

        // Helper routine
        str += "keysFromPassword(password)\n";
        str += "   FOR p is all values of password\n";
        str += "     keyset += indexFromCharacter(*p)\n";
        str += "   key.a <- (keyset / 2) % size\n";
        str += "   i <- 0\n";
        str += "   WHILE gcd(key.a - i, size) does not equal 1\n";
        str += "     i += 1\n";
        str += "   key.a <- key.a - i\n";
        str += "   key.b <- keyset % size\n";
        str += "   RETURN key\n\n";

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

        // find a Affine password from a textual password
        Key key = keysFromPassword(password);

        // convert the plaintext one character at a time
        for (const char* p = plainText.c_str(); *p; p++)
        {
            // convert the character into an index we can work with
            int index = indexFromCharacter(*p);

            // send the index into the ciphertext
            cipherText += characterFromIndex(((index * key.a) + key.b) % sizeAlphabet);
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

        // find a Affine password from a textual password
        Key key = keysFromPassword(password);

        // convert the plaintext one character at a time
        for (const char* c = cipherText.c_str(); *c; c++)
        {
           // convert the character into an index we can work with
           int index = indexFromCharacter(*c);

           int p = ((modInverse(key.a, sizeAlphabet) * (index - key.b) % sizeAlphabet) + sizeAlphabet) % sizeAlphabet;

           // send the index into the plaintext
           plainText += characterFromIndex(p);
        }

        return plainText;
    }    
private:
    /**************************************************
     * INDEX FROM CHARACTER
     * Get an index value from a given letter.
     *************************************************/
    int indexFromCharacter(char letter)
    {
        if (letter > valueMaximum || letter < valueMinimum)
            return 0;
        else
            return (int)(letter - valueMinimum);
    }

    /**************************************************
     * CHARACTER FROM INDEX
     * Get the characer value from a given index.
     *************************************************/
    char characterFromIndex(int index)
    {
        if (index >= 0 && index < sizeAlphabet)
            return (char)(index + valueMinimum);
        else
            return ' ';
    }

    /**************************************************
     * SET Key
     * Get the integer values from the text password
     *************************************************/
    Key keysFromPassword(std::string password)
    {
        Key key;
        int keyset = 0;
        for (std::string::const_iterator it = password.begin();
            it != password.end();
            ++it)
            keyset += indexFromCharacter(*it);
        key.a = (keyset / 2) % sizeAlphabet;
        int i = 0;

        while (gcd(key.a - i, sizeAlphabet) != 1)
            i++;

        key.a = key.a - i;
        key.b = keyset % sizeAlphabet;

        return key;
    }

    /**************************************************
     * GCD
     * Get the greatest common denominator
     *************************************************/
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        a %= b;
        return gcd(b, a);
    }

    /**************************************************
     * MOD INVERSE
     * Get the multiplicative inverse of a;
     *************************************************/
    int modInverse(int a, int m)
    {
        a = a % m;
        for (int x = 1; x < m; x++)
        {
            if ((a * x) % m == 1)
                return x;
        }
    }
    // minimum "printable" character
    char valueMinimum;

    // maximum "printable" character
    char valueMaximum;

    int sizeAlphabet;
};

#endif // CIPHER01_H