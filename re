import re
with open('/etc/passwd') as f: c = f.read()
 
print c
 
#test r'' and re.M
print re.findall('^(\\w+):',         c      )       #['root']
print re.findall(r'^(\w+):',         c      )       #['root']
print re.findall(r'^(\w+):',         c, re.M)       #['root',                ..,  'puppet']
print re.findall(r'\w+(?=:x:)',      c, re.M)       #['root',                ..,  'puppet']  #lookahead
print re.findall(r'^(\w+):.*:(.+)$', c, re.M)       #[('root', '/bin/bash'), .., ('puppet', '/bin/false')]
 
#test match(), search, findall, finditer()
print re.findall (r'^(\w+):.*:(.+)$', c, re.M)                                   #[('root', '/bin/bash'), .., ('puppet', '/bin/false')]
print re.finditer(r'^(\w+):.*:(.+)$', c, re.M)                                   #<callable-iterator object at 0x7f8c69fb8390>
print re.search  (r'^(\w+):.*:(.+)$', c, re.M)                                   #<_sre.SRE_Match object at 0x7f8c69eab250>
print re.match   (r'^(\w+):.*:(.+)$', c, re.M)                                   #<_sre.SRE_Match object at 0x7f8c69eab0b8>
for l in re.findall (r'^(\w+):.*:(.+)$', c, re.M): print l                       #('root', '/bin/bash'),..,('puppet', '/bin/false')
for m in re.finditer(r'^(\w+):.*:(.+)$', c, re.M): print (m.group(1), m.group(2))#('root', '/bin/bash'),..,('puppet', '/bin/false')
m =      re.search  (r'^(\w+):.*:(.+)$', c, re.M); print (m.group(1), m.group(2))#('root', '/bin/bash')
m =      re.match   (r'^(\w+):.*:(.+)$', c, re.M); print (m.group(1), m.group(2))#('root', '/bin/bash')       
 
#test regex named group(P means placeholder), 
#myview named groups are for search() or match()
m = re.match   (r'(root):.*:(.+)$', c, re.M);                print(m.group(1), m.group(2))          #('root', '/bin/bash')
m = re.search (r'^(root):.*:(.+)$', c, re.M);                print(m.group(1), m.group(2))          #('root', '/bin/bash')
m = re.search (r'^(?P<id>root):.*:(?P<shell>.+)$', c, re.M); print(m.group('id'), m.group(2))       #('root', '/bin/bash')
m = re.search (r'^(?P<id>root):.*:(?P<shell>.+)$', c, re.M); print(m.group('id'), m.group('shell')) #('root', '/bin/bash')
l = re.findall(r'^(?P<id>root):.*:(?P<shell>.+)$', c, re.M); print l                                #[('root', '/bin/bash')]
 
#re.I, (?i), (?imx)
for m in re.finditer(r'.*BASH$', c, re.M)     : print m.group(0)
for m in re.finditer(r'.*BASH$', c, re.M|re.I): print m.group(0)
for m in re.finditer(r'(?im).*BASH$', c)      : print m.group(0)

 
#split into list in the bondary of \W+
print re.findall(r'\w+'         , c, re.M) #same as
print re.findall(r'\w+'         , c)       #same as
print re.split(r'\W+'           , c)       #same as
print re.split(r'[^a-zA-Z0-9_]+', c)       #['root', 'x', '0', '0', 'root', 'root',...,'']
print re.split(r'\W+'           , c, 1)    #['root', 'x:0:0:root:/root...\n]
print re.split(r'\W+'           , c, 2)    #['root', 'x', '0:0:root:/root...\n']
print re.split(r'(\W+)'         , c, 2)    #['root', ':', 'x', ':', '0:0:root...\n']
