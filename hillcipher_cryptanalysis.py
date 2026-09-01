import numpy as np

plaintext=input("enter the plaintext : ")
ciphertext=input("enter the ciphertext : ")
n=int(input("enter the size of square matrix : "))

plain=[]
cipher=[]

for i in range(0,len(plaintext),n):

    text=plaintext[i:i+n]
    plain.append([ord(ch)-ord('a') for ch in text])

for i in range(0,len(ciphertext),n):

    text=ciphertext[i:i+n]
    cipher.append([ord(ch)-ord('a') for ch in text])

plain=np.array(plain)
cipher=np.array(cipher)

print("Plain : ",plain)
print("Cipher : ",cipher)



det=np.round(np.linalg.det(plain))
det=det%26

det_inv=pow(int(det),-1,26)

adj=np.round(det*np.linalg.inv(plain)).astype(int)

inv_p=(det_inv*adj)%26

K=(inv_p @ cipher)%26

print("key : ", K)
