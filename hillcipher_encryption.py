plaintext=input("enter the plaintext : ")
n=int(input("enter the size of square matrix : "))

key=[]

for i in range(n):

    row=[]

    for j in range(n):

        row.append(int(input(f"[{i}][{j}] : ")))

    key.append(row)

plain=[]

while (len(plaintext)%n!=0):

    plaintext+='x'

for i in range(0,len(plaintext),n):

    text=plaintext[i:i+n]

    plain.append([ord(ch)-ord('a') for ch in text])


cipher =[]

for ch in plain:

    row=[]

    for i in range(n):

        s=0

        for j in range(n):

            s+=ch[j]*key[j][i]

        row.append(s%26)

    cipher.append(row)

ciphertext=""

for block in cipher:

    for x in block:

        ciphertext+=chr(x+ord('A'))

print("the cipher text is : ",ciphertext)


