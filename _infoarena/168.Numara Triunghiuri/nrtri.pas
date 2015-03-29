var bufin:array[1..65000]of byte;
    n,i,j,t:longint;
    a:array[1..801]of longint;
    iesi:boolean;
    cont:int64;

function cautare_binara(x:longint):longint;
var v,m,u:longint;

begin

  u := j+1 ; v := n ;      //cautare binara 50pt
  while u<=v do
  begin
    m := (u+v) div 2;
{    if a[m] = x then
    begin
      cautare_binara := m;
      exit;
    end
    else     }
    begin
      if x >= a[m] then u := m+1
      else  v := m-1;
    end;

  end;


  cautare_binara := v;
{
  u := j ; v := n+1;              //cautare binara 100pt
  while v-u > 1 do
  begin
    m := (u+v)div 2;
    if x >= a[m] then
      u := m
    else
      v := m ;
  end;

  cautare_binara := u;}
end;

begin
  assign(input,'nrtri.in'); reset(input);
  assign(output,'nrtri.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);  cont := 0;
  for i := 1 to n do read(a[i]);

  repeat
    iesi := true;
    for i := 1 to n-1 do
      if a[i] > a[i+1] then
      begin
        t := a[i];
        a[i] := a[i+1];
        a[i+1] := t;
        iesi := false;
      end;

    until iesi = true;

  for i := 1 to n - 2 do
    for j := i+1 to n-1 do
    begin
      cont := cont + cautare_binara(a[i]+a[j]) - j ;

    end;

  write(cont);
  close(input);
  close(output);
end.
