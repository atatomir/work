var n,i,j,ies:word;
    f:text;
    a:array[1..10000,1..10000]of byte;
    grp:boolean;
    gr:longword;

begin
  assign(f,'rama.in'); reset(f);
  readln(f,n);
  gr:=0;
  for i := 1 to n do
    for j := 1 to n do
    begin
      read(f,a[i,j]);
      if a[i,j]=0 then inc(gr);
    end;
  close(f);
  assign(f,'rama.out');rewrite(f);writeln(f,gr div 2);
  grp:= false;
  i:=1;
  while i <=(n+1 div 2) do
  begin
    for j := i to n-i+1 do
      if a[i,j]=0 then
      begin
        if grp= false then grp:=true else
        begin
          writeln(f,i,' ',j);
          grp:= false;
        end;
      end;
    for j := i+1 to n-i+1 do
      if a[j,n-i+1]=0 then
      begin
        if grp= false then grp:=true else
        begin
          writeln(f,j,' ',n-i+1);
          grp:= false;
        end;
      end;
    for j := n-i downto i do
      if a[n-i+1,j]=0 then
      begin
        if grp= false then grp:=true else
        begin
          writeln(f,n-i+1,' ',j);
          grp:= false;
        end;
      end;
    for j := n-i downto i+1 do
      if a[j,i]=0 then
      begin
        if grp= false then grp:=true else
        begin
          writeln(f,j,' ',i);
          grp:= false;
        end;
      end;
    inc(i);
  end;
  close(f);
end.
