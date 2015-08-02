var a,b:array[1..10000] of byte;
    r:array[1..20000] of byte;
    cf1,cf2,i,j,x,rm:word;
    c:char;
    f:text;
    //prima:boolean;

begin
  assign(f,'inmultire.in'); reset(f);
  readln(f,cf1);
  for i := 1 to cf1 do
  begin
    read(f,c);
    a[i]:=(ord(c)-$30);
  end;
  readln(f,cf2);
  for i := 1 to cf2 do
  begin
    read(f,c);
    b[i]:=(ord(c)-$30);
  end;
  close(f);

  assign(f,'inmultire.out'); rewrite(f);
  for i := 1 to 20000 do r[i] := 0;

  for i := cf2 downto 1 do
  begin
    rm:=0;
    for j:= cf1 downto 1 do
    begin
      x:=  a[j]*b[i] + rm + r[20000-cf2+i-cf1+j] ;
      r[20000-cf2+i-cf1+j] :=  x mod 10;
      rm := x div 10;
      //writeln(rm);
    end;
    r[20000-cf2+i-cf1] := rm;
  end;

  j:=1;
  while r[j]=0 do j:= j+1;
  for i := j to 20000 do write(f,r[i]);
  close(f);
end.

