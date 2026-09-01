import numpy as np

ciphertext=input("enter the ciphertext : ")
n=int(input("enter the size of square matrix : "))

key=[]

for i in range(n):

    row=[]

    for j in range(n):

        row.append(int(input(f"[{i}][{j}] : ")))

    key.append(row)

key=np.array(key) # making it a numpy array

cipher=[]

# padding is not required since cipher text will already be proper

for i in range(0,len(ciphertext),n):

    text=ciphertext[i:i+n]

    cipher.append([ord(ch)-ord('a') for ch in text])

# inverse of key
#===========================
det = np.round(np.linalg.det(key))
det= det%26

det_inv=pow(int(det),-1,26)

adj = np.round(det*np.linalg.inv(key)).astype(int)

inv_key=(det_inv*adj)%26
print(inv_key)
#===========================

plain =[]

for ch in cipher:

    row=[]

    for i in range(n):

        s=0

        for j in range(n):

            s+=ch[j]*inv_key[j][i]

        row.append(s%26)

    plain.append(row)

plaintext=""

for block in plain:

    for x in block:

        plaintext+=chr(x+ord('A'))

print("the plain text is : ",plaintext)



