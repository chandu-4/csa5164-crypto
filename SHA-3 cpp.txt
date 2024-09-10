#import hashlib
text = hashlib.sha1(b'hello')
encrypt = text.hexdigest()
print(encrypt)
