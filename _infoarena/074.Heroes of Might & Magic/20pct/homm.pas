var f,fout:text;
    tf:array[2..101,2..101]of boolean;
    a:array[1..20,1..102,1..102]of longint;
    n,m,k:longint;
    x1,y1,x2,y2:Longint;
    z:int64;
    i,j,l,max:Longint;

begin
  assign(f,'homm.in'); reset(f);
  readln(f,m,n,k);



  for i := 1 to m do
  begin
    for j := 1 to n do
    begin
      if j = n then
        readln(f,z) else read(f,z);
      if z = 0 then tf[i+1,j+1] := true
      else
      tf[i+1,j+1] := false;
    end;
  end;
  read(f,x1,y1,x2,y2); close(f);


  for l:= 1 to k do
    for i:= 1 to m+2 do
      for j := 1 to n+2 do
        a[l,i,j]:=0;

  if x1 <> 1 then a[1,x1,y1+1]:=1 ;
  if x1 <> m then a[1,x1+2,y1+1]:=1 ;
  if y1 <> 1 then a[1,x1+1,y1]:=1;
  if y1 <> n then a[1,x1+1,y1+2]:=1;

  assign(fout,'homm.out');rewrite(fout);

  max :=a[1,x2+1,y2+1];

  for l := 2 to k do
  begin
    for i := 2 to m+1 do
      for j := 2 to n+1 do
      begin
        if tf[i,j]= true then
          a[l,i,j] :=  a[l-1,i+1,j]+a[l-1,i-1,j]+a[l-1,i,j+1]+a[l-1,i,j-1] ;
      end;


    max := max + a[l,x2+1,y2+1];


  end;

  writeln(fout,max);

  {for l := 1 to k do
  begin
    for i := 1 to m do
    begin
      for j := 1 to n do
        write(fout,a[l,i+1,j+1],' ');
    writeln(fout);
    end;
    writeln(fout);
  end;}

  close(fout);



end.
