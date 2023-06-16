**Cipher**: The Procedure i.e. Mechanism that converts **ClearText** into **CipherText** using, for instance, a Key.

**Symmetric Key Ciphers**: The Key that is used to Encrypt Clear-Text into CipherText can also be used to decrypt i.e. convert CipherText into ClearText. This mechanism is also called the Shared Key System.

**Asymmetric Key Ciphers / Public - Private Key Systems / RSA**: 
- All Keys exist in Pairs.
- One Key is declared as Private and the other is declared as Public
- ClearText can be Encrypted with either of these Keys. When ClearText has been Encrypted with one Key it can only be decrypted using the other Key.

**Diffie-Hellman key Exchange**: Symmetric Key Ciphers are the basis for this method of Communication. The Key is exchanged physically before any secured communication can be initiated. This mechanism has been superseded by the **RSA** Ciphers.

**Hashing**: Hash is a representation of data that is reproducible but not reversible. Hashing Functions are an example of One-Way Functions. Information is lost when Hash is calculated for data. This ensures that the original data cannot be calculated using only the Hash. E.g. of Hashing Algorithms are **MD5** and **SHA-1**. 

The Measure of a good Hashing Algorithm is how well it prevents Collisions. Collision refers to a scenario where two different pieces of Input Data produce the same Hash. 

**Digital Signatures**: These are a combination of Hashing Algorithms and Keys. Signature looks like a Hash and is created using the input Data and a Key. The signature is reproducible provided the Data and the Key doesn't change. This can help 3rd Parties confirm that the Data was provided by the intended provider and changed by Malicious actors during transmission.

**Key Derivation**: Key Derivation is done through recursive Hashing. Data is Hashed and then the Hash is Hashed and so on and so forth. 

A Key is derived after many cycles of Hashing. With each cycle it becomes more and more Computationally expensive to verify the Hash. Key Derivation is generally used with Passwords to prevent Brute-Force Dictionary Attacks on the Passwords.

**Salt**: Salt is a Random Alpha-Numeric string that is concatenated with the Hash of the user’s password and then Hashed before storage in the Database. The Original Password is never stored anywhere in the system. 

Salting is used to address the possibility of a precomputed Hash Attack. In practice people reuse their passwords. Data brokers are able to generate lists of most used passwords. 

Attackers can use these lists to generate Hashes for the most commonly used passwords. These Hashes are then used for Brute-Force Attacks on the Database. Salting makes the stored Hashes prohibitively long and computationally expensive to Brute-Force. Even if a common password is used, salting can make it unbreakable through pre-computed Hash Attacks.

**Brute-Force Attack**: Aim of a Brute-Force attack is to compromise password based security by trying every possible iteration of password. This is the simplest form of attack and is very costly to perform. Provided enough raw compute power Brute-Force Attacks are viable.

**Pattern Analysis / Cryptanalysis**: It is the Art of finding patterns in Encrypted messages and decrypting without requiring a Key. Today Machine Learning can be used to perform Cryptanalysis.

**Entropy**: Entropy is defined as the Lack of Order or Predictability; gradual descent into disorder. Entropy is the degree of randomness. For computers there is no such thing as “Random”. Best we can do is make things appear as random as possible. 

**CSPRNG**: Stands for cryptographically Secure Pseudo Random Number Generation.    

**Restricted Algorithms**: Opposite of Open Standards like RSA, AES. Restricted algorithms are Ciphers that are proprietary and Closed Sourced. 

These are only viable for low security applications given the risk of disclosure of the algorithm to the general public. Furthermore, there is no possibility of real-world quality control.  

**Keyspace**: The range of the possible values of a key

**Stream vs. Block Algorithms**: Stream and Block algorithms are a subcategory of Symmetric key Algorithms. Stream Algorithms process the cleartext one bit / byte at a time. Block Algorithms process the cleartext in blocks of predefined sizes usually 64-Bit blocks.

**Cryptosystem**: The Cipher together with the keys, plaintext and ciphertext are called the cryptosystem.

**Compromise**: The loss of the private / secret key is called a Compromise.

**Computationally Secure**: A Cipher is only considered computationally secure if the available system resources, current or future, are not enough to break the cipher.

**Nonce**: A nonce is a random alpha-numeric number used only once in a cryptographic communication. Many nonces also include a timestamp to ensure exact timeliness, though this requires clock synchronization between organizations. Nonce is used to prevent **Replay-Attacks**.

**Replay / Playback Attack**: Valid transmissions are recorded and then resent at a later time by Malicious Actors.

**Vigener Cipher**: The characters of the ClearText and the Key are converted into Integers based on their position in the alphabet. The corresponding number of the key and the ClearText are then added to obtain the number for the CipherText. 

If the Key is shorter than the length of the ClearText message, then the key is repeatedly concatenated with itself to equal it to the length of the ClearText.


---

#### Good Cryptography
Cryptographic Ciphers perform pretty much Black-Box Black-Magic to secure data. Good cryptography obscures data in such a way that makes it Difficult and Costly to duplicate or reverse.

**Algorithmic Complexity**: As the Computers become more powerful and the advancements in specialized hardware that is great at doing math i.e. GPUs, Cryptographic Algorithms must be made more Costly to compute. 

Algorithms that were previously considered ideally secure are no longer considered secure for this very reason. E.g. **MCrypt** was the standard Cryptography Library on PHP for many years which was superseded by AES which will likely be superseded by **LibSodium (NaCL)**.

**Larger Keys**: In Asymmetric Key Systems, Larger keys can make the systems more secure. E.g. Google recommends that sites use a **2K Key** which means it is a 2048 Byte Prime Number. The number of possible combinations increase exponentially as the key sizes increase.

E.g. the possible combinations for a 8-Digit key are 108 i.e. Eight positions and 10 possible values on each Position.


---

#### Digital Signature Certificates
Alice sends a business document to Bob with a signature certificate.

Signature certificate has been Signed with Alice's Private key and can only be verified using Alice's Public key.

Signature Certificate contains the Hash of the accompanying business document. 

When Bob decrypts the Signature certificate, If the signature certificate decrypts successfully using Alice's Public key, it confirms that the signature came from Alice. This is because only Alice has her Private key which was used to Sign the digital Signature certificate.

Once the Hash has been extracted from the Signature certificate, Bob compares it to the Hash of the Business Document. If the Hash matches, it confirms that contents of the business document have not been altered during transit.

*Note*: A party can have multiple public-key/private-key pairs. One pair for encryption/decryption and another for signing / verification.


---

#### Password Hashing
Passwords should not be stored in clear-text inside a database. One-way functions can be used to calculate the hash of the password which is then stored in the DB. 

When a user logs-in, the hash of the password can be calculated and compared against the value in the DB. If the hashes match, the user is allowed to login.

The advantage is that even the admin of the database will not be able to view the stored passwords. If the password needs to be reset, the database admin can simply remove the hash of the password from the database.

This method is known to be employed by popular email providers.

This method is not completely secure though. For instance an attacker may still be able to copy the password hashes. 

Common hashing functions include SHA1, SHA-256 and MD5. If the attacker is aware of the hashing function used by the entity, he may be able to execute the hashing function against a dictionary of common password used ( i.e. dictionary attack)

This way the attacker will be able to recover some of the passwords used.


---

#### User Authentication
User authentication can be secured using public-private keys.

At the time the user is created his public and private keys are calculated by the application. 

Private key is given to the user (method?) and the public key is stored in the server DB.

Update: The Key Pair could be calculated on the client side, in the browser. The Private key can be stored in the browser's local storage and the Public key can be transmitted to the server.

Problem: The Cipher used for key calculation must be able to produce reproducible key pairs. If the keys are reproducible then the user will not lose access to the system in case the Private key is deleted from the User's browser.

Another Problem: If the Key Pair are reproducible there is a risk that the Keys could also be calculated by Malory. The choice of the Cipher will be the deciding factor in this case.

Every time the user logs-in, the server will verify the user through the following method.
1. Host sends random generated string to user in clear-text (safe?)
2. User encrypts the string with her private key and sends back to the server her name and the random string
3. Server looks up Alice's public key from DB and verifies Alice's identity.

