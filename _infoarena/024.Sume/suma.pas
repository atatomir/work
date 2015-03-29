var a:array[1..25000]of longint;
    b:array[1..250]of longint;
    p:longint;
    n:longint;
    i,j,k:longint;
    f,fo:text;
    flag:boolean;
    s,s2:int64;

begin
  assign(f,'sume.in'); reset(f);
  readln(f,p);

  n := (trunc(sqrt(2*p)))+1;

  for i := 1 to n do
    read(f,a[i]);



  assign(fo,'sume.out'); rewrite(fo);


  b[1]:=(a[1]+a[2]-a[n]) div 2;


  for i := 2 to n do
  begin
    b[i]:= a[i-1]-b[1];
  end;

  flag:=false;
  for i := 1 to n do
    if b[i] <=0 then
    begin
      flag:=true;
      break;
    end;

  if flag = false then
  begin
    s:=0;
    for i := 1 to n do
      s := s + a[i];
    for i := n+1 to p do
    begin
      read(f,a[i]);
      s:= s + a[i];
    end;
    s := s div (n-1);
    s2:=0;
    for i := 1 to n do
      s2:=s2 + b[i];
    if s <>s2 then flag:=true;
    if flag = false then
    begin
      k := n  ;
      for i := 2 to n - 1 do
      begin
        for j := i + 1 to n do
        begin
          flag :=  ( (b[i] + b[j]) <> a[k]);
          k := k +1;
          if flag then break;
        end;
        if flag then break;
      end;

    end;
  end;


  if flag = true then write(fo,'-1')
  else
  begin
    writeln(fo,n);
    for i := 1 to n do
      write(fo,b[i],' ');
  end;

  close(fo);
  close(f);
end.
