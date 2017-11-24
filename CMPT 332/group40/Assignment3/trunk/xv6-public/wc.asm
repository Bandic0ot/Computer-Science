
_wc:     file format elf32-i386


Disassembly of section .text:

00000000 <wc>:

char buf[512];

void
wc(int fd, char *name)
{
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 28             	sub    $0x28,%esp
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
   6:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%ebp)
   d:	8b 45 e8             	mov    -0x18(%ebp),%eax
  10:	89 45 ec             	mov    %eax,-0x14(%ebp)
  13:	8b 45 ec             	mov    -0x14(%ebp),%eax
  16:	89 45 f0             	mov    %eax,-0x10(%ebp)
  inword = 0;
  19:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
  while((n = read(fd, buf, sizeof(buf))) > 0){
  20:	eb 69                	jmp    8b <wc+0x8b>
    for(i=0; i<n; i++){
  22:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  29:	eb 58                	jmp    83 <wc+0x83>
      c++;
  2b:	83 45 e8 01          	addl   $0x1,-0x18(%ebp)
      if(buf[i] == '\n')
  2f:	8b 45 f4             	mov    -0xc(%ebp),%eax
  32:	05 40 0c 00 00       	add    $0xc40,%eax
  37:	0f b6 00             	movzbl (%eax),%eax
  3a:	3c 0a                	cmp    $0xa,%al
  3c:	75 04                	jne    42 <wc+0x42>
        l++;
  3e:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
      if(strchr(" \r\t\n\v", buf[i]))
  42:	8b 45 f4             	mov    -0xc(%ebp),%eax
  45:	05 40 0c 00 00       	add    $0xc40,%eax
  4a:	0f b6 00             	movzbl (%eax),%eax
  4d:	0f be c0             	movsbl %al,%eax
  50:	83 ec 08             	sub    $0x8,%esp
  53:	50                   	push   %eax
  54:	68 40 09 00 00       	push   $0x940
  59:	e8 34 02 00 00       	call   292 <strchr>
  5e:	83 c4 10             	add    $0x10,%esp
  61:	85 c0                	test   %eax,%eax
  63:	74 09                	je     6e <wc+0x6e>
        inword = 0;
  65:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
  6c:	eb 11                	jmp    7f <wc+0x7f>
      else if(!inword){
  6e:	83 7d e4 00          	cmpl   $0x0,-0x1c(%ebp)
  72:	75 0b                	jne    7f <wc+0x7f>
        w++;
  74:	83 45 ec 01          	addl   $0x1,-0x14(%ebp)
        inword = 1;
  78:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%ebp)
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
  7f:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  83:	8b 45 f4             	mov    -0xc(%ebp),%eax
  86:	3b 45 e0             	cmp    -0x20(%ebp),%eax
  89:	7c a0                	jl     2b <wc+0x2b>
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
  8b:	83 ec 04             	sub    $0x4,%esp
  8e:	68 00 02 00 00       	push   $0x200
  93:	68 40 0c 00 00       	push   $0xc40
  98:	ff 75 08             	pushl  0x8(%ebp)
  9b:	e8 8b 03 00 00       	call   42b <read>
  a0:	83 c4 10             	add    $0x10,%esp
  a3:	89 45 e0             	mov    %eax,-0x20(%ebp)
  a6:	83 7d e0 00          	cmpl   $0x0,-0x20(%ebp)
  aa:	0f 8f 72 ff ff ff    	jg     22 <wc+0x22>
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
  b0:	83 7d e0 00          	cmpl   $0x0,-0x20(%ebp)
  b4:	79 17                	jns    cd <wc+0xcd>
    printf(1, "wc: read error\n");
  b6:	83 ec 08             	sub    $0x8,%esp
  b9:	68 46 09 00 00       	push   $0x946
  be:	6a 01                	push   $0x1
  c0:	e8 c5 04 00 00       	call   58a <printf>
  c5:	83 c4 10             	add    $0x10,%esp
    exit();
  c8:	e8 46 03 00 00       	call   413 <exit>
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
  cd:	83 ec 08             	sub    $0x8,%esp
  d0:	ff 75 0c             	pushl  0xc(%ebp)
  d3:	ff 75 e8             	pushl  -0x18(%ebp)
  d6:	ff 75 ec             	pushl  -0x14(%ebp)
  d9:	ff 75 f0             	pushl  -0x10(%ebp)
  dc:	68 56 09 00 00       	push   $0x956
  e1:	6a 01                	push   $0x1
  e3:	e8 a2 04 00 00       	call   58a <printf>
  e8:	83 c4 20             	add    $0x20,%esp
}
  eb:	c9                   	leave  
  ec:	c3                   	ret    

000000ed <main>:

int
main(int argc, char *argv[])
{
  ed:	8d 4c 24 04          	lea    0x4(%esp),%ecx
  f1:	83 e4 f0             	and    $0xfffffff0,%esp
  f4:	ff 71 fc             	pushl  -0x4(%ecx)
  f7:	55                   	push   %ebp
  f8:	89 e5                	mov    %esp,%ebp
  fa:	53                   	push   %ebx
  fb:	51                   	push   %ecx
  fc:	83 ec 10             	sub    $0x10,%esp
  ff:	89 cb                	mov    %ecx,%ebx
  int fd, i;

  if(argc <= 1){
 101:	83 3b 01             	cmpl   $0x1,(%ebx)
 104:	7f 17                	jg     11d <main+0x30>
    wc(0, "");
 106:	83 ec 08             	sub    $0x8,%esp
 109:	68 63 09 00 00       	push   $0x963
 10e:	6a 00                	push   $0x0
 110:	e8 eb fe ff ff       	call   0 <wc>
 115:	83 c4 10             	add    $0x10,%esp
    exit();
 118:	e8 f6 02 00 00       	call   413 <exit>
  }

  for(i = 1; i < argc; i++){
 11d:	c7 45 f4 01 00 00 00 	movl   $0x1,-0xc(%ebp)
 124:	e9 83 00 00 00       	jmp    1ac <main+0xbf>
    if((fd = open(argv[i], 0)) < 0){
 129:	8b 45 f4             	mov    -0xc(%ebp),%eax
 12c:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 133:	8b 43 04             	mov    0x4(%ebx),%eax
 136:	01 d0                	add    %edx,%eax
 138:	8b 00                	mov    (%eax),%eax
 13a:	83 ec 08             	sub    $0x8,%esp
 13d:	6a 00                	push   $0x0
 13f:	50                   	push   %eax
 140:	e8 0e 03 00 00       	call   453 <open>
 145:	83 c4 10             	add    $0x10,%esp
 148:	89 45 f0             	mov    %eax,-0x10(%ebp)
 14b:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 14f:	79 29                	jns    17a <main+0x8d>
      printf(1, "wc: cannot open %s\n", argv[i]);
 151:	8b 45 f4             	mov    -0xc(%ebp),%eax
 154:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 15b:	8b 43 04             	mov    0x4(%ebx),%eax
 15e:	01 d0                	add    %edx,%eax
 160:	8b 00                	mov    (%eax),%eax
 162:	83 ec 04             	sub    $0x4,%esp
 165:	50                   	push   %eax
 166:	68 64 09 00 00       	push   $0x964
 16b:	6a 01                	push   $0x1
 16d:	e8 18 04 00 00       	call   58a <printf>
 172:	83 c4 10             	add    $0x10,%esp
      exit();
 175:	e8 99 02 00 00       	call   413 <exit>
    }
    wc(fd, argv[i]);
 17a:	8b 45 f4             	mov    -0xc(%ebp),%eax
 17d:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
 184:	8b 43 04             	mov    0x4(%ebx),%eax
 187:	01 d0                	add    %edx,%eax
 189:	8b 00                	mov    (%eax),%eax
 18b:	83 ec 08             	sub    $0x8,%esp
 18e:	50                   	push   %eax
 18f:	ff 75 f0             	pushl  -0x10(%ebp)
 192:	e8 69 fe ff ff       	call   0 <wc>
 197:	83 c4 10             	add    $0x10,%esp
    close(fd);
 19a:	83 ec 0c             	sub    $0xc,%esp
 19d:	ff 75 f0             	pushl  -0x10(%ebp)
 1a0:	e8 96 02 00 00       	call   43b <close>
 1a5:	83 c4 10             	add    $0x10,%esp
  if(argc <= 1){
    wc(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
 1a8:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
 1ac:	8b 45 f4             	mov    -0xc(%ebp),%eax
 1af:	3b 03                	cmp    (%ebx),%eax
 1b1:	0f 8c 72 ff ff ff    	jl     129 <main+0x3c>
      exit();
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit();
 1b7:	e8 57 02 00 00       	call   413 <exit>

000001bc <stosb>:
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt)
{
 1bc:	55                   	push   %ebp
 1bd:	89 e5                	mov    %esp,%ebp
 1bf:	57                   	push   %edi
 1c0:	53                   	push   %ebx
  asm volatile("cld; rep stosb" :
 1c1:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1c4:	8b 55 10             	mov    0x10(%ebp),%edx
 1c7:	8b 45 0c             	mov    0xc(%ebp),%eax
 1ca:	89 cb                	mov    %ecx,%ebx
 1cc:	89 df                	mov    %ebx,%edi
 1ce:	89 d1                	mov    %edx,%ecx
 1d0:	fc                   	cld    
 1d1:	f3 aa                	rep stos %al,%es:(%edi)
 1d3:	89 ca                	mov    %ecx,%edx
 1d5:	89 fb                	mov    %edi,%ebx
 1d7:	89 5d 08             	mov    %ebx,0x8(%ebp)
 1da:	89 55 10             	mov    %edx,0x10(%ebp)
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}
 1dd:	90                   	nop
 1de:	5b                   	pop    %ebx
 1df:	5f                   	pop    %edi
 1e0:	5d                   	pop    %ebp
 1e1:	c3                   	ret    

000001e2 <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, char *t)
{
 1e2:	55                   	push   %ebp
 1e3:	89 e5                	mov    %esp,%ebp
 1e5:	83 ec 10             	sub    $0x10,%esp
  char *os;

  os = s;
 1e8:	8b 45 08             	mov    0x8(%ebp),%eax
 1eb:	89 45 fc             	mov    %eax,-0x4(%ebp)
  while((*s++ = *t++) != 0)
 1ee:	90                   	nop
 1ef:	8b 45 08             	mov    0x8(%ebp),%eax
 1f2:	8d 50 01             	lea    0x1(%eax),%edx
 1f5:	89 55 08             	mov    %edx,0x8(%ebp)
 1f8:	8b 55 0c             	mov    0xc(%ebp),%edx
 1fb:	8d 4a 01             	lea    0x1(%edx),%ecx
 1fe:	89 4d 0c             	mov    %ecx,0xc(%ebp)
 201:	0f b6 12             	movzbl (%edx),%edx
 204:	88 10                	mov    %dl,(%eax)
 206:	0f b6 00             	movzbl (%eax),%eax
 209:	84 c0                	test   %al,%al
 20b:	75 e2                	jne    1ef <strcpy+0xd>
    ;
  return os;
 20d:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 210:	c9                   	leave  
 211:	c3                   	ret    

00000212 <strcmp>:

int
strcmp(const char *p, const char *q)
{
 212:	55                   	push   %ebp
 213:	89 e5                	mov    %esp,%ebp
  while(*p && *p == *q)
 215:	eb 08                	jmp    21f <strcmp+0xd>
    p++, q++;
 217:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 21b:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
 21f:	8b 45 08             	mov    0x8(%ebp),%eax
 222:	0f b6 00             	movzbl (%eax),%eax
 225:	84 c0                	test   %al,%al
 227:	74 10                	je     239 <strcmp+0x27>
 229:	8b 45 08             	mov    0x8(%ebp),%eax
 22c:	0f b6 10             	movzbl (%eax),%edx
 22f:	8b 45 0c             	mov    0xc(%ebp),%eax
 232:	0f b6 00             	movzbl (%eax),%eax
 235:	38 c2                	cmp    %al,%dl
 237:	74 de                	je     217 <strcmp+0x5>
    p++, q++;
  return (uchar)*p - (uchar)*q;
 239:	8b 45 08             	mov    0x8(%ebp),%eax
 23c:	0f b6 00             	movzbl (%eax),%eax
 23f:	0f b6 d0             	movzbl %al,%edx
 242:	8b 45 0c             	mov    0xc(%ebp),%eax
 245:	0f b6 00             	movzbl (%eax),%eax
 248:	0f b6 c0             	movzbl %al,%eax
 24b:	29 c2                	sub    %eax,%edx
 24d:	89 d0                	mov    %edx,%eax
}
 24f:	5d                   	pop    %ebp
 250:	c3                   	ret    

00000251 <strlen>:

uint
strlen(char *s)
{
 251:	55                   	push   %ebp
 252:	89 e5                	mov    %esp,%ebp
 254:	83 ec 10             	sub    $0x10,%esp
  int n;

  for(n = 0; s[n]; n++)
 257:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
 25e:	eb 04                	jmp    264 <strlen+0x13>
 260:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
 264:	8b 55 fc             	mov    -0x4(%ebp),%edx
 267:	8b 45 08             	mov    0x8(%ebp),%eax
 26a:	01 d0                	add    %edx,%eax
 26c:	0f b6 00             	movzbl (%eax),%eax
 26f:	84 c0                	test   %al,%al
 271:	75 ed                	jne    260 <strlen+0xf>
    ;
  return n;
 273:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 276:	c9                   	leave  
 277:	c3                   	ret    

00000278 <memset>:

void*
memset(void *dst, int c, uint n)
{
 278:	55                   	push   %ebp
 279:	89 e5                	mov    %esp,%ebp
  stosb(dst, c, n);
 27b:	8b 45 10             	mov    0x10(%ebp),%eax
 27e:	50                   	push   %eax
 27f:	ff 75 0c             	pushl  0xc(%ebp)
 282:	ff 75 08             	pushl  0x8(%ebp)
 285:	e8 32 ff ff ff       	call   1bc <stosb>
 28a:	83 c4 0c             	add    $0xc,%esp
  return dst;
 28d:	8b 45 08             	mov    0x8(%ebp),%eax
}
 290:	c9                   	leave  
 291:	c3                   	ret    

00000292 <strchr>:

char*
strchr(const char *s, char c)
{
 292:	55                   	push   %ebp
 293:	89 e5                	mov    %esp,%ebp
 295:	83 ec 04             	sub    $0x4,%esp
 298:	8b 45 0c             	mov    0xc(%ebp),%eax
 29b:	88 45 fc             	mov    %al,-0x4(%ebp)
  for(; *s; s++)
 29e:	eb 14                	jmp    2b4 <strchr+0x22>
    if(*s == c)
 2a0:	8b 45 08             	mov    0x8(%ebp),%eax
 2a3:	0f b6 00             	movzbl (%eax),%eax
 2a6:	3a 45 fc             	cmp    -0x4(%ebp),%al
 2a9:	75 05                	jne    2b0 <strchr+0x1e>
      return (char*)s;
 2ab:	8b 45 08             	mov    0x8(%ebp),%eax
 2ae:	eb 13                	jmp    2c3 <strchr+0x31>
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
 2b0:	83 45 08 01          	addl   $0x1,0x8(%ebp)
 2b4:	8b 45 08             	mov    0x8(%ebp),%eax
 2b7:	0f b6 00             	movzbl (%eax),%eax
 2ba:	84 c0                	test   %al,%al
 2bc:	75 e2                	jne    2a0 <strchr+0xe>
    if(*s == c)
      return (char*)s;
  return 0;
 2be:	b8 00 00 00 00       	mov    $0x0,%eax
}
 2c3:	c9                   	leave  
 2c4:	c3                   	ret    

000002c5 <gets>:

char*
gets(char *buf, int max)
{
 2c5:	55                   	push   %ebp
 2c6:	89 e5                	mov    %esp,%ebp
 2c8:	83 ec 18             	sub    $0x18,%esp
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 2cb:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
 2d2:	eb 42                	jmp    316 <gets+0x51>
    cc = read(0, &c, 1);
 2d4:	83 ec 04             	sub    $0x4,%esp
 2d7:	6a 01                	push   $0x1
 2d9:	8d 45 ef             	lea    -0x11(%ebp),%eax
 2dc:	50                   	push   %eax
 2dd:	6a 00                	push   $0x0
 2df:	e8 47 01 00 00       	call   42b <read>
 2e4:	83 c4 10             	add    $0x10,%esp
 2e7:	89 45 f0             	mov    %eax,-0x10(%ebp)
    if(cc < 1)
 2ea:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 2ee:	7e 33                	jle    323 <gets+0x5e>
      break;
    buf[i++] = c;
 2f0:	8b 45 f4             	mov    -0xc(%ebp),%eax
 2f3:	8d 50 01             	lea    0x1(%eax),%edx
 2f6:	89 55 f4             	mov    %edx,-0xc(%ebp)
 2f9:	89 c2                	mov    %eax,%edx
 2fb:	8b 45 08             	mov    0x8(%ebp),%eax
 2fe:	01 c2                	add    %eax,%edx
 300:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 304:	88 02                	mov    %al,(%edx)
    if(c == '\n' || c == '\r')
 306:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 30a:	3c 0a                	cmp    $0xa,%al
 30c:	74 16                	je     324 <gets+0x5f>
 30e:	0f b6 45 ef          	movzbl -0x11(%ebp),%eax
 312:	3c 0d                	cmp    $0xd,%al
 314:	74 0e                	je     324 <gets+0x5f>
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
 316:	8b 45 f4             	mov    -0xc(%ebp),%eax
 319:	83 c0 01             	add    $0x1,%eax
 31c:	3b 45 0c             	cmp    0xc(%ebp),%eax
 31f:	7c b3                	jl     2d4 <gets+0xf>
 321:	eb 01                	jmp    324 <gets+0x5f>
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
 323:	90                   	nop
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
 324:	8b 55 f4             	mov    -0xc(%ebp),%edx
 327:	8b 45 08             	mov    0x8(%ebp),%eax
 32a:	01 d0                	add    %edx,%eax
 32c:	c6 00 00             	movb   $0x0,(%eax)
  return buf;
 32f:	8b 45 08             	mov    0x8(%ebp),%eax
}
 332:	c9                   	leave  
 333:	c3                   	ret    

00000334 <stat>:

int
stat(char *n, struct stat *st)
{
 334:	55                   	push   %ebp
 335:	89 e5                	mov    %esp,%ebp
 337:	83 ec 18             	sub    $0x18,%esp
  int fd;
  int r;

  fd = open(n, O_RDONLY);
 33a:	83 ec 08             	sub    $0x8,%esp
 33d:	6a 00                	push   $0x0
 33f:	ff 75 08             	pushl  0x8(%ebp)
 342:	e8 0c 01 00 00       	call   453 <open>
 347:	83 c4 10             	add    $0x10,%esp
 34a:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(fd < 0)
 34d:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 351:	79 07                	jns    35a <stat+0x26>
    return -1;
 353:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 358:	eb 25                	jmp    37f <stat+0x4b>
  r = fstat(fd, st);
 35a:	83 ec 08             	sub    $0x8,%esp
 35d:	ff 75 0c             	pushl  0xc(%ebp)
 360:	ff 75 f4             	pushl  -0xc(%ebp)
 363:	e8 03 01 00 00       	call   46b <fstat>
 368:	83 c4 10             	add    $0x10,%esp
 36b:	89 45 f0             	mov    %eax,-0x10(%ebp)
  close(fd);
 36e:	83 ec 0c             	sub    $0xc,%esp
 371:	ff 75 f4             	pushl  -0xc(%ebp)
 374:	e8 c2 00 00 00       	call   43b <close>
 379:	83 c4 10             	add    $0x10,%esp
  return r;
 37c:	8b 45 f0             	mov    -0x10(%ebp),%eax
}
 37f:	c9                   	leave  
 380:	c3                   	ret    

00000381 <atoi>:

int
atoi(const char *s)
{
 381:	55                   	push   %ebp
 382:	89 e5                	mov    %esp,%ebp
 384:	83 ec 10             	sub    $0x10,%esp
  int n;

  n = 0;
 387:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  while('0' <= *s && *s <= '9')
 38e:	eb 25                	jmp    3b5 <atoi+0x34>
    n = n*10 + *s++ - '0';
 390:	8b 55 fc             	mov    -0x4(%ebp),%edx
 393:	89 d0                	mov    %edx,%eax
 395:	c1 e0 02             	shl    $0x2,%eax
 398:	01 d0                	add    %edx,%eax
 39a:	01 c0                	add    %eax,%eax
 39c:	89 c1                	mov    %eax,%ecx
 39e:	8b 45 08             	mov    0x8(%ebp),%eax
 3a1:	8d 50 01             	lea    0x1(%eax),%edx
 3a4:	89 55 08             	mov    %edx,0x8(%ebp)
 3a7:	0f b6 00             	movzbl (%eax),%eax
 3aa:	0f be c0             	movsbl %al,%eax
 3ad:	01 c8                	add    %ecx,%eax
 3af:	83 e8 30             	sub    $0x30,%eax
 3b2:	89 45 fc             	mov    %eax,-0x4(%ebp)
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
 3b5:	8b 45 08             	mov    0x8(%ebp),%eax
 3b8:	0f b6 00             	movzbl (%eax),%eax
 3bb:	3c 2f                	cmp    $0x2f,%al
 3bd:	7e 0a                	jle    3c9 <atoi+0x48>
 3bf:	8b 45 08             	mov    0x8(%ebp),%eax
 3c2:	0f b6 00             	movzbl (%eax),%eax
 3c5:	3c 39                	cmp    $0x39,%al
 3c7:	7e c7                	jle    390 <atoi+0xf>
    n = n*10 + *s++ - '0';
  return n;
 3c9:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
 3cc:	c9                   	leave  
 3cd:	c3                   	ret    

000003ce <memmove>:

void*
memmove(void *vdst, void *vsrc, int n)
{
 3ce:	55                   	push   %ebp
 3cf:	89 e5                	mov    %esp,%ebp
 3d1:	83 ec 10             	sub    $0x10,%esp
  char *dst, *src;
  
  dst = vdst;
 3d4:	8b 45 08             	mov    0x8(%ebp),%eax
 3d7:	89 45 fc             	mov    %eax,-0x4(%ebp)
  src = vsrc;
 3da:	8b 45 0c             	mov    0xc(%ebp),%eax
 3dd:	89 45 f8             	mov    %eax,-0x8(%ebp)
  while(n-- > 0)
 3e0:	eb 17                	jmp    3f9 <memmove+0x2b>
    *dst++ = *src++;
 3e2:	8b 45 fc             	mov    -0x4(%ebp),%eax
 3e5:	8d 50 01             	lea    0x1(%eax),%edx
 3e8:	89 55 fc             	mov    %edx,-0x4(%ebp)
 3eb:	8b 55 f8             	mov    -0x8(%ebp),%edx
 3ee:	8d 4a 01             	lea    0x1(%edx),%ecx
 3f1:	89 4d f8             	mov    %ecx,-0x8(%ebp)
 3f4:	0f b6 12             	movzbl (%edx),%edx
 3f7:	88 10                	mov    %dl,(%eax)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
 3f9:	8b 45 10             	mov    0x10(%ebp),%eax
 3fc:	8d 50 ff             	lea    -0x1(%eax),%edx
 3ff:	89 55 10             	mov    %edx,0x10(%ebp)
 402:	85 c0                	test   %eax,%eax
 404:	7f dc                	jg     3e2 <memmove+0x14>
    *dst++ = *src++;
  return vdst;
 406:	8b 45 08             	mov    0x8(%ebp),%eax
}
 409:	c9                   	leave  
 40a:	c3                   	ret    

0000040b <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
 40b:	b8 01 00 00 00       	mov    $0x1,%eax
 410:	cd 40                	int    $0x40
 412:	c3                   	ret    

00000413 <exit>:
SYSCALL(exit)
 413:	b8 02 00 00 00       	mov    $0x2,%eax
 418:	cd 40                	int    $0x40
 41a:	c3                   	ret    

0000041b <wait>:
SYSCALL(wait)
 41b:	b8 03 00 00 00       	mov    $0x3,%eax
 420:	cd 40                	int    $0x40
 422:	c3                   	ret    

00000423 <pipe>:
SYSCALL(pipe)
 423:	b8 04 00 00 00       	mov    $0x4,%eax
 428:	cd 40                	int    $0x40
 42a:	c3                   	ret    

0000042b <read>:
SYSCALL(read)
 42b:	b8 05 00 00 00       	mov    $0x5,%eax
 430:	cd 40                	int    $0x40
 432:	c3                   	ret    

00000433 <write>:
SYSCALL(write)
 433:	b8 10 00 00 00       	mov    $0x10,%eax
 438:	cd 40                	int    $0x40
 43a:	c3                   	ret    

0000043b <close>:
SYSCALL(close)
 43b:	b8 15 00 00 00       	mov    $0x15,%eax
 440:	cd 40                	int    $0x40
 442:	c3                   	ret    

00000443 <kill>:
SYSCALL(kill)
 443:	b8 06 00 00 00       	mov    $0x6,%eax
 448:	cd 40                	int    $0x40
 44a:	c3                   	ret    

0000044b <exec>:
SYSCALL(exec)
 44b:	b8 07 00 00 00       	mov    $0x7,%eax
 450:	cd 40                	int    $0x40
 452:	c3                   	ret    

00000453 <open>:
SYSCALL(open)
 453:	b8 0f 00 00 00       	mov    $0xf,%eax
 458:	cd 40                	int    $0x40
 45a:	c3                   	ret    

0000045b <mknod>:
SYSCALL(mknod)
 45b:	b8 11 00 00 00       	mov    $0x11,%eax
 460:	cd 40                	int    $0x40
 462:	c3                   	ret    

00000463 <unlink>:
SYSCALL(unlink)
 463:	b8 12 00 00 00       	mov    $0x12,%eax
 468:	cd 40                	int    $0x40
 46a:	c3                   	ret    

0000046b <fstat>:
SYSCALL(fstat)
 46b:	b8 08 00 00 00       	mov    $0x8,%eax
 470:	cd 40                	int    $0x40
 472:	c3                   	ret    

00000473 <link>:
SYSCALL(link)
 473:	b8 13 00 00 00       	mov    $0x13,%eax
 478:	cd 40                	int    $0x40
 47a:	c3                   	ret    

0000047b <mkdir>:
SYSCALL(mkdir)
 47b:	b8 14 00 00 00       	mov    $0x14,%eax
 480:	cd 40                	int    $0x40
 482:	c3                   	ret    

00000483 <chdir>:
SYSCALL(chdir)
 483:	b8 09 00 00 00       	mov    $0x9,%eax
 488:	cd 40                	int    $0x40
 48a:	c3                   	ret    

0000048b <dup>:
SYSCALL(dup)
 48b:	b8 0a 00 00 00       	mov    $0xa,%eax
 490:	cd 40                	int    $0x40
 492:	c3                   	ret    

00000493 <getpid>:
SYSCALL(getpid)
 493:	b8 0b 00 00 00       	mov    $0xb,%eax
 498:	cd 40                	int    $0x40
 49a:	c3                   	ret    

0000049b <sbrk>:
SYSCALL(sbrk)
 49b:	b8 0c 00 00 00       	mov    $0xc,%eax
 4a0:	cd 40                	int    $0x40
 4a2:	c3                   	ret    

000004a3 <sleep>:
SYSCALL(sleep)
 4a3:	b8 0d 00 00 00       	mov    $0xd,%eax
 4a8:	cd 40                	int    $0x40
 4aa:	c3                   	ret    

000004ab <uptime>:
SYSCALL(uptime)
 4ab:	b8 0e 00 00 00       	mov    $0xe,%eax
 4b0:	cd 40                	int    $0x40
 4b2:	c3                   	ret    

000004b3 <putc>:
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
 4b3:	55                   	push   %ebp
 4b4:	89 e5                	mov    %esp,%ebp
 4b6:	83 ec 18             	sub    $0x18,%esp
 4b9:	8b 45 0c             	mov    0xc(%ebp),%eax
 4bc:	88 45 f4             	mov    %al,-0xc(%ebp)
  write(fd, &c, 1);
 4bf:	83 ec 04             	sub    $0x4,%esp
 4c2:	6a 01                	push   $0x1
 4c4:	8d 45 f4             	lea    -0xc(%ebp),%eax
 4c7:	50                   	push   %eax
 4c8:	ff 75 08             	pushl  0x8(%ebp)
 4cb:	e8 63 ff ff ff       	call   433 <write>
 4d0:	83 c4 10             	add    $0x10,%esp
}
 4d3:	90                   	nop
 4d4:	c9                   	leave  
 4d5:	c3                   	ret    

000004d6 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
 4d6:	55                   	push   %ebp
 4d7:	89 e5                	mov    %esp,%ebp
 4d9:	53                   	push   %ebx
 4da:	83 ec 24             	sub    $0x24,%esp
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
 4dd:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  if(sgn && xx < 0){
 4e4:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
 4e8:	74 17                	je     501 <printint+0x2b>
 4ea:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
 4ee:	79 11                	jns    501 <printint+0x2b>
    neg = 1;
 4f0:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
    x = -xx;
 4f7:	8b 45 0c             	mov    0xc(%ebp),%eax
 4fa:	f7 d8                	neg    %eax
 4fc:	89 45 ec             	mov    %eax,-0x14(%ebp)
 4ff:	eb 06                	jmp    507 <printint+0x31>
  } else {
    x = xx;
 501:	8b 45 0c             	mov    0xc(%ebp),%eax
 504:	89 45 ec             	mov    %eax,-0x14(%ebp)
  }

  i = 0;
 507:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  do{
    buf[i++] = digits[x % base];
 50e:	8b 4d f4             	mov    -0xc(%ebp),%ecx
 511:	8d 41 01             	lea    0x1(%ecx),%eax
 514:	89 45 f4             	mov    %eax,-0xc(%ebp)
 517:	8b 5d 10             	mov    0x10(%ebp),%ebx
 51a:	8b 45 ec             	mov    -0x14(%ebp),%eax
 51d:	ba 00 00 00 00       	mov    $0x0,%edx
 522:	f7 f3                	div    %ebx
 524:	89 d0                	mov    %edx,%eax
 526:	0f b6 80 ec 0b 00 00 	movzbl 0xbec(%eax),%eax
 52d:	88 44 0d dc          	mov    %al,-0x24(%ebp,%ecx,1)
  }while((x /= base) != 0);
 531:	8b 5d 10             	mov    0x10(%ebp),%ebx
 534:	8b 45 ec             	mov    -0x14(%ebp),%eax
 537:	ba 00 00 00 00       	mov    $0x0,%edx
 53c:	f7 f3                	div    %ebx
 53e:	89 45 ec             	mov    %eax,-0x14(%ebp)
 541:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 545:	75 c7                	jne    50e <printint+0x38>
  if(neg)
 547:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 54b:	74 2d                	je     57a <printint+0xa4>
    buf[i++] = '-';
 54d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 550:	8d 50 01             	lea    0x1(%eax),%edx
 553:	89 55 f4             	mov    %edx,-0xc(%ebp)
 556:	c6 44 05 dc 2d       	movb   $0x2d,-0x24(%ebp,%eax,1)

  while(--i >= 0)
 55b:	eb 1d                	jmp    57a <printint+0xa4>
    putc(fd, buf[i]);
 55d:	8d 55 dc             	lea    -0x24(%ebp),%edx
 560:	8b 45 f4             	mov    -0xc(%ebp),%eax
 563:	01 d0                	add    %edx,%eax
 565:	0f b6 00             	movzbl (%eax),%eax
 568:	0f be c0             	movsbl %al,%eax
 56b:	83 ec 08             	sub    $0x8,%esp
 56e:	50                   	push   %eax
 56f:	ff 75 08             	pushl  0x8(%ebp)
 572:	e8 3c ff ff ff       	call   4b3 <putc>
 577:	83 c4 10             	add    $0x10,%esp
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
 57a:	83 6d f4 01          	subl   $0x1,-0xc(%ebp)
 57e:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 582:	79 d9                	jns    55d <printint+0x87>
    putc(fd, buf[i]);
}
 584:	90                   	nop
 585:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 588:	c9                   	leave  
 589:	c3                   	ret    

0000058a <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, char *fmt, ...)
{
 58a:	55                   	push   %ebp
 58b:	89 e5                	mov    %esp,%ebp
 58d:	83 ec 28             	sub    $0x28,%esp
  char *s;
  int c, i, state;
  uint *ap;

  state = 0;
 590:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  ap = (uint*)(void*)&fmt + 1;
 597:	8d 45 0c             	lea    0xc(%ebp),%eax
 59a:	83 c0 04             	add    $0x4,%eax
 59d:	89 45 e8             	mov    %eax,-0x18(%ebp)
  for(i = 0; fmt[i]; i++){
 5a0:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 5a7:	e9 59 01 00 00       	jmp    705 <printf+0x17b>
    c = fmt[i] & 0xff;
 5ac:	8b 55 0c             	mov    0xc(%ebp),%edx
 5af:	8b 45 f0             	mov    -0x10(%ebp),%eax
 5b2:	01 d0                	add    %edx,%eax
 5b4:	0f b6 00             	movzbl (%eax),%eax
 5b7:	0f be c0             	movsbl %al,%eax
 5ba:	25 ff 00 00 00       	and    $0xff,%eax
 5bf:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    if(state == 0){
 5c2:	83 7d ec 00          	cmpl   $0x0,-0x14(%ebp)
 5c6:	75 2c                	jne    5f4 <printf+0x6a>
      if(c == '%'){
 5c8:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 5cc:	75 0c                	jne    5da <printf+0x50>
        state = '%';
 5ce:	c7 45 ec 25 00 00 00 	movl   $0x25,-0x14(%ebp)
 5d5:	e9 27 01 00 00       	jmp    701 <printf+0x177>
      } else {
        putc(fd, c);
 5da:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 5dd:	0f be c0             	movsbl %al,%eax
 5e0:	83 ec 08             	sub    $0x8,%esp
 5e3:	50                   	push   %eax
 5e4:	ff 75 08             	pushl  0x8(%ebp)
 5e7:	e8 c7 fe ff ff       	call   4b3 <putc>
 5ec:	83 c4 10             	add    $0x10,%esp
 5ef:	e9 0d 01 00 00       	jmp    701 <printf+0x177>
      }
    } else if(state == '%'){
 5f4:	83 7d ec 25          	cmpl   $0x25,-0x14(%ebp)
 5f8:	0f 85 03 01 00 00    	jne    701 <printf+0x177>
      if(c == 'd'){
 5fe:	83 7d e4 64          	cmpl   $0x64,-0x1c(%ebp)
 602:	75 1e                	jne    622 <printf+0x98>
        printint(fd, *ap, 10, 1);
 604:	8b 45 e8             	mov    -0x18(%ebp),%eax
 607:	8b 00                	mov    (%eax),%eax
 609:	6a 01                	push   $0x1
 60b:	6a 0a                	push   $0xa
 60d:	50                   	push   %eax
 60e:	ff 75 08             	pushl  0x8(%ebp)
 611:	e8 c0 fe ff ff       	call   4d6 <printint>
 616:	83 c4 10             	add    $0x10,%esp
        ap++;
 619:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 61d:	e9 d8 00 00 00       	jmp    6fa <printf+0x170>
      } else if(c == 'x' || c == 'p'){
 622:	83 7d e4 78          	cmpl   $0x78,-0x1c(%ebp)
 626:	74 06                	je     62e <printf+0xa4>
 628:	83 7d e4 70          	cmpl   $0x70,-0x1c(%ebp)
 62c:	75 1e                	jne    64c <printf+0xc2>
        printint(fd, *ap, 16, 0);
 62e:	8b 45 e8             	mov    -0x18(%ebp),%eax
 631:	8b 00                	mov    (%eax),%eax
 633:	6a 00                	push   $0x0
 635:	6a 10                	push   $0x10
 637:	50                   	push   %eax
 638:	ff 75 08             	pushl  0x8(%ebp)
 63b:	e8 96 fe ff ff       	call   4d6 <printint>
 640:	83 c4 10             	add    $0x10,%esp
        ap++;
 643:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 647:	e9 ae 00 00 00       	jmp    6fa <printf+0x170>
      } else if(c == 's'){
 64c:	83 7d e4 73          	cmpl   $0x73,-0x1c(%ebp)
 650:	75 43                	jne    695 <printf+0x10b>
        s = (char*)*ap;
 652:	8b 45 e8             	mov    -0x18(%ebp),%eax
 655:	8b 00                	mov    (%eax),%eax
 657:	89 45 f4             	mov    %eax,-0xc(%ebp)
        ap++;
 65a:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
        if(s == 0)
 65e:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 662:	75 25                	jne    689 <printf+0xff>
          s = "(null)";
 664:	c7 45 f4 78 09 00 00 	movl   $0x978,-0xc(%ebp)
        while(*s != 0){
 66b:	eb 1c                	jmp    689 <printf+0xff>
          putc(fd, *s);
 66d:	8b 45 f4             	mov    -0xc(%ebp),%eax
 670:	0f b6 00             	movzbl (%eax),%eax
 673:	0f be c0             	movsbl %al,%eax
 676:	83 ec 08             	sub    $0x8,%esp
 679:	50                   	push   %eax
 67a:	ff 75 08             	pushl  0x8(%ebp)
 67d:	e8 31 fe ff ff       	call   4b3 <putc>
 682:	83 c4 10             	add    $0x10,%esp
          s++;
 685:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
 689:	8b 45 f4             	mov    -0xc(%ebp),%eax
 68c:	0f b6 00             	movzbl (%eax),%eax
 68f:	84 c0                	test   %al,%al
 691:	75 da                	jne    66d <printf+0xe3>
 693:	eb 65                	jmp    6fa <printf+0x170>
          putc(fd, *s);
          s++;
        }
      } else if(c == 'c'){
 695:	83 7d e4 63          	cmpl   $0x63,-0x1c(%ebp)
 699:	75 1d                	jne    6b8 <printf+0x12e>
        putc(fd, *ap);
 69b:	8b 45 e8             	mov    -0x18(%ebp),%eax
 69e:	8b 00                	mov    (%eax),%eax
 6a0:	0f be c0             	movsbl %al,%eax
 6a3:	83 ec 08             	sub    $0x8,%esp
 6a6:	50                   	push   %eax
 6a7:	ff 75 08             	pushl  0x8(%ebp)
 6aa:	e8 04 fe ff ff       	call   4b3 <putc>
 6af:	83 c4 10             	add    $0x10,%esp
        ap++;
 6b2:	83 45 e8 04          	addl   $0x4,-0x18(%ebp)
 6b6:	eb 42                	jmp    6fa <printf+0x170>
      } else if(c == '%'){
 6b8:	83 7d e4 25          	cmpl   $0x25,-0x1c(%ebp)
 6bc:	75 17                	jne    6d5 <printf+0x14b>
        putc(fd, c);
 6be:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 6c1:	0f be c0             	movsbl %al,%eax
 6c4:	83 ec 08             	sub    $0x8,%esp
 6c7:	50                   	push   %eax
 6c8:	ff 75 08             	pushl  0x8(%ebp)
 6cb:	e8 e3 fd ff ff       	call   4b3 <putc>
 6d0:	83 c4 10             	add    $0x10,%esp
 6d3:	eb 25                	jmp    6fa <printf+0x170>
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
 6d5:	83 ec 08             	sub    $0x8,%esp
 6d8:	6a 25                	push   $0x25
 6da:	ff 75 08             	pushl  0x8(%ebp)
 6dd:	e8 d1 fd ff ff       	call   4b3 <putc>
 6e2:	83 c4 10             	add    $0x10,%esp
        putc(fd, c);
 6e5:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 6e8:	0f be c0             	movsbl %al,%eax
 6eb:	83 ec 08             	sub    $0x8,%esp
 6ee:	50                   	push   %eax
 6ef:	ff 75 08             	pushl  0x8(%ebp)
 6f2:	e8 bc fd ff ff       	call   4b3 <putc>
 6f7:	83 c4 10             	add    $0x10,%esp
      }
      state = 0;
 6fa:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  int c, i, state;
  uint *ap;

  state = 0;
  ap = (uint*)(void*)&fmt + 1;
  for(i = 0; fmt[i]; i++){
 701:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 705:	8b 55 0c             	mov    0xc(%ebp),%edx
 708:	8b 45 f0             	mov    -0x10(%ebp),%eax
 70b:	01 d0                	add    %edx,%eax
 70d:	0f b6 00             	movzbl (%eax),%eax
 710:	84 c0                	test   %al,%al
 712:	0f 85 94 fe ff ff    	jne    5ac <printf+0x22>
        putc(fd, c);
      }
      state = 0;
    }
  }
}
 718:	90                   	nop
 719:	c9                   	leave  
 71a:	c3                   	ret    

0000071b <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
 71b:	55                   	push   %ebp
 71c:	89 e5                	mov    %esp,%ebp
 71e:	83 ec 10             	sub    $0x10,%esp
  Header *bp, *p;

  bp = (Header*)ap - 1;
 721:	8b 45 08             	mov    0x8(%ebp),%eax
 724:	83 e8 08             	sub    $0x8,%eax
 727:	89 45 f8             	mov    %eax,-0x8(%ebp)
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 72a:	a1 08 0c 00 00       	mov    0xc08,%eax
 72f:	89 45 fc             	mov    %eax,-0x4(%ebp)
 732:	eb 24                	jmp    758 <free+0x3d>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
 734:	8b 45 fc             	mov    -0x4(%ebp),%eax
 737:	8b 00                	mov    (%eax),%eax
 739:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 73c:	77 12                	ja     750 <free+0x35>
 73e:	8b 45 f8             	mov    -0x8(%ebp),%eax
 741:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 744:	77 24                	ja     76a <free+0x4f>
 746:	8b 45 fc             	mov    -0x4(%ebp),%eax
 749:	8b 00                	mov    (%eax),%eax
 74b:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 74e:	77 1a                	ja     76a <free+0x4f>
free(void *ap)
{
  Header *bp, *p;

  bp = (Header*)ap - 1;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
 750:	8b 45 fc             	mov    -0x4(%ebp),%eax
 753:	8b 00                	mov    (%eax),%eax
 755:	89 45 fc             	mov    %eax,-0x4(%ebp)
 758:	8b 45 f8             	mov    -0x8(%ebp),%eax
 75b:	3b 45 fc             	cmp    -0x4(%ebp),%eax
 75e:	76 d4                	jbe    734 <free+0x19>
 760:	8b 45 fc             	mov    -0x4(%ebp),%eax
 763:	8b 00                	mov    (%eax),%eax
 765:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 768:	76 ca                	jbe    734 <free+0x19>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
 76a:	8b 45 f8             	mov    -0x8(%ebp),%eax
 76d:	8b 40 04             	mov    0x4(%eax),%eax
 770:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 777:	8b 45 f8             	mov    -0x8(%ebp),%eax
 77a:	01 c2                	add    %eax,%edx
 77c:	8b 45 fc             	mov    -0x4(%ebp),%eax
 77f:	8b 00                	mov    (%eax),%eax
 781:	39 c2                	cmp    %eax,%edx
 783:	75 24                	jne    7a9 <free+0x8e>
    bp->s.size += p->s.ptr->s.size;
 785:	8b 45 f8             	mov    -0x8(%ebp),%eax
 788:	8b 50 04             	mov    0x4(%eax),%edx
 78b:	8b 45 fc             	mov    -0x4(%ebp),%eax
 78e:	8b 00                	mov    (%eax),%eax
 790:	8b 40 04             	mov    0x4(%eax),%eax
 793:	01 c2                	add    %eax,%edx
 795:	8b 45 f8             	mov    -0x8(%ebp),%eax
 798:	89 50 04             	mov    %edx,0x4(%eax)
    bp->s.ptr = p->s.ptr->s.ptr;
 79b:	8b 45 fc             	mov    -0x4(%ebp),%eax
 79e:	8b 00                	mov    (%eax),%eax
 7a0:	8b 10                	mov    (%eax),%edx
 7a2:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7a5:	89 10                	mov    %edx,(%eax)
 7a7:	eb 0a                	jmp    7b3 <free+0x98>
  } else
    bp->s.ptr = p->s.ptr;
 7a9:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7ac:	8b 10                	mov    (%eax),%edx
 7ae:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7b1:	89 10                	mov    %edx,(%eax)
  if(p + p->s.size == bp){
 7b3:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7b6:	8b 40 04             	mov    0x4(%eax),%eax
 7b9:	8d 14 c5 00 00 00 00 	lea    0x0(,%eax,8),%edx
 7c0:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7c3:	01 d0                	add    %edx,%eax
 7c5:	3b 45 f8             	cmp    -0x8(%ebp),%eax
 7c8:	75 20                	jne    7ea <free+0xcf>
    p->s.size += bp->s.size;
 7ca:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7cd:	8b 50 04             	mov    0x4(%eax),%edx
 7d0:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7d3:	8b 40 04             	mov    0x4(%eax),%eax
 7d6:	01 c2                	add    %eax,%edx
 7d8:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7db:	89 50 04             	mov    %edx,0x4(%eax)
    p->s.ptr = bp->s.ptr;
 7de:	8b 45 f8             	mov    -0x8(%ebp),%eax
 7e1:	8b 10                	mov    (%eax),%edx
 7e3:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7e6:	89 10                	mov    %edx,(%eax)
 7e8:	eb 08                	jmp    7f2 <free+0xd7>
  } else
    p->s.ptr = bp;
 7ea:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7ed:	8b 55 f8             	mov    -0x8(%ebp),%edx
 7f0:	89 10                	mov    %edx,(%eax)
  freep = p;
 7f2:	8b 45 fc             	mov    -0x4(%ebp),%eax
 7f5:	a3 08 0c 00 00       	mov    %eax,0xc08
}
 7fa:	90                   	nop
 7fb:	c9                   	leave  
 7fc:	c3                   	ret    

000007fd <morecore>:

static Header*
morecore(uint nu)
{
 7fd:	55                   	push   %ebp
 7fe:	89 e5                	mov    %esp,%ebp
 800:	83 ec 18             	sub    $0x18,%esp
  char *p;
  Header *hp;

  if(nu < 4096)
 803:	81 7d 08 ff 0f 00 00 	cmpl   $0xfff,0x8(%ebp)
 80a:	77 07                	ja     813 <morecore+0x16>
    nu = 4096;
 80c:	c7 45 08 00 10 00 00 	movl   $0x1000,0x8(%ebp)
  p = sbrk(nu * sizeof(Header));
 813:	8b 45 08             	mov    0x8(%ebp),%eax
 816:	c1 e0 03             	shl    $0x3,%eax
 819:	83 ec 0c             	sub    $0xc,%esp
 81c:	50                   	push   %eax
 81d:	e8 79 fc ff ff       	call   49b <sbrk>
 822:	83 c4 10             	add    $0x10,%esp
 825:	89 45 f4             	mov    %eax,-0xc(%ebp)
  if(p == (char*)-1)
 828:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 82c:	75 07                	jne    835 <morecore+0x38>
    return 0;
 82e:	b8 00 00 00 00       	mov    $0x0,%eax
 833:	eb 26                	jmp    85b <morecore+0x5e>
  hp = (Header*)p;
 835:	8b 45 f4             	mov    -0xc(%ebp),%eax
 838:	89 45 f0             	mov    %eax,-0x10(%ebp)
  hp->s.size = nu;
 83b:	8b 45 f0             	mov    -0x10(%ebp),%eax
 83e:	8b 55 08             	mov    0x8(%ebp),%edx
 841:	89 50 04             	mov    %edx,0x4(%eax)
  free((void*)(hp + 1));
 844:	8b 45 f0             	mov    -0x10(%ebp),%eax
 847:	83 c0 08             	add    $0x8,%eax
 84a:	83 ec 0c             	sub    $0xc,%esp
 84d:	50                   	push   %eax
 84e:	e8 c8 fe ff ff       	call   71b <free>
 853:	83 c4 10             	add    $0x10,%esp
  return freep;
 856:	a1 08 0c 00 00       	mov    0xc08,%eax
}
 85b:	c9                   	leave  
 85c:	c3                   	ret    

0000085d <malloc>:

void*
malloc(uint nbytes)
{
 85d:	55                   	push   %ebp
 85e:	89 e5                	mov    %esp,%ebp
 860:	83 ec 18             	sub    $0x18,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
 863:	8b 45 08             	mov    0x8(%ebp),%eax
 866:	83 c0 07             	add    $0x7,%eax
 869:	c1 e8 03             	shr    $0x3,%eax
 86c:	83 c0 01             	add    $0x1,%eax
 86f:	89 45 ec             	mov    %eax,-0x14(%ebp)
  if((prevp = freep) == 0){
 872:	a1 08 0c 00 00       	mov    0xc08,%eax
 877:	89 45 f0             	mov    %eax,-0x10(%ebp)
 87a:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 87e:	75 23                	jne    8a3 <malloc+0x46>
    base.s.ptr = freep = prevp = &base;
 880:	c7 45 f0 00 0c 00 00 	movl   $0xc00,-0x10(%ebp)
 887:	8b 45 f0             	mov    -0x10(%ebp),%eax
 88a:	a3 08 0c 00 00       	mov    %eax,0xc08
 88f:	a1 08 0c 00 00       	mov    0xc08,%eax
 894:	a3 00 0c 00 00       	mov    %eax,0xc00
    base.s.size = 0;
 899:	c7 05 04 0c 00 00 00 	movl   $0x0,0xc04
 8a0:	00 00 00 
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 8a3:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8a6:	8b 00                	mov    (%eax),%eax
 8a8:	89 45 f4             	mov    %eax,-0xc(%ebp)
    if(p->s.size >= nunits){
 8ab:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8ae:	8b 40 04             	mov    0x4(%eax),%eax
 8b1:	3b 45 ec             	cmp    -0x14(%ebp),%eax
 8b4:	72 4d                	jb     903 <malloc+0xa6>
      if(p->s.size == nunits)
 8b6:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8b9:	8b 40 04             	mov    0x4(%eax),%eax
 8bc:	3b 45 ec             	cmp    -0x14(%ebp),%eax
 8bf:	75 0c                	jne    8cd <malloc+0x70>
        prevp->s.ptr = p->s.ptr;
 8c1:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8c4:	8b 10                	mov    (%eax),%edx
 8c6:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8c9:	89 10                	mov    %edx,(%eax)
 8cb:	eb 26                	jmp    8f3 <malloc+0x96>
      else {
        p->s.size -= nunits;
 8cd:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8d0:	8b 40 04             	mov    0x4(%eax),%eax
 8d3:	2b 45 ec             	sub    -0x14(%ebp),%eax
 8d6:	89 c2                	mov    %eax,%edx
 8d8:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8db:	89 50 04             	mov    %edx,0x4(%eax)
        p += p->s.size;
 8de:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8e1:	8b 40 04             	mov    0x4(%eax),%eax
 8e4:	c1 e0 03             	shl    $0x3,%eax
 8e7:	01 45 f4             	add    %eax,-0xc(%ebp)
        p->s.size = nunits;
 8ea:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8ed:	8b 55 ec             	mov    -0x14(%ebp),%edx
 8f0:	89 50 04             	mov    %edx,0x4(%eax)
      }
      freep = prevp;
 8f3:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8f6:	a3 08 0c 00 00       	mov    %eax,0xc08
      return (void*)(p + 1);
 8fb:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8fe:	83 c0 08             	add    $0x8,%eax
 901:	eb 3b                	jmp    93e <malloc+0xe1>
    }
    if(p == freep)
 903:	a1 08 0c 00 00       	mov    0xc08,%eax
 908:	39 45 f4             	cmp    %eax,-0xc(%ebp)
 90b:	75 1e                	jne    92b <malloc+0xce>
      if((p = morecore(nunits)) == 0)
 90d:	83 ec 0c             	sub    $0xc,%esp
 910:	ff 75 ec             	pushl  -0x14(%ebp)
 913:	e8 e5 fe ff ff       	call   7fd <morecore>
 918:	83 c4 10             	add    $0x10,%esp
 91b:	89 45 f4             	mov    %eax,-0xc(%ebp)
 91e:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
 922:	75 07                	jne    92b <malloc+0xce>
        return 0;
 924:	b8 00 00 00 00       	mov    $0x0,%eax
 929:	eb 13                	jmp    93e <malloc+0xe1>
  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
 92b:	8b 45 f4             	mov    -0xc(%ebp),%eax
 92e:	89 45 f0             	mov    %eax,-0x10(%ebp)
 931:	8b 45 f4             	mov    -0xc(%ebp),%eax
 934:	8b 00                	mov    (%eax),%eax
 936:	89 45 f4             	mov    %eax,-0xc(%ebp)
      return (void*)(p + 1);
    }
    if(p == freep)
      if((p = morecore(nunits)) == 0)
        return 0;
  }
 939:	e9 6d ff ff ff       	jmp    8ab <malloc+0x4e>
}
 93e:	c9                   	leave  
 93f:	c3                   	ret    
