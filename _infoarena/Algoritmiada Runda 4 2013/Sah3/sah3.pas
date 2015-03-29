var n,m,i,j,n2,m2,d,v,k:longint;
    bufin:array[1..65000]of byte;
    a,b:array[0..1001,0..1001]of longint;
    cont:int64;

function patrat(x,y,dim:longint):boolean;
var li,lj,v1,z:longint;
    //s1:int64;
begin
  patrat := false;
  v1 := a[x+dim-1,y];

  {s1 := 0;
  for li := x to x + dim-1 do
    for lj := y to y + dim -1 do
      s1 := s1 + a[li,lj];

  if dim mod 2 = 1 then
  begin
    if s1 <> ((dim*dim div 2)+1)*a[x,y] + (dim*dim div 2)*a[x+1,y] then exit;
  end
  else
    if s1 <> (dim*dim div 2) * (a[x,y]+ a[x+1,y]) then exit;   }
                         //verifica diag secundara
  li := x; lj := y + dim -1;
  for z := 1 to dim do
  begin
    if v1 <> a[li,lj] then exit;
    inc(li); dec(lj);
  end;

                          // verifica toate liniile

  for li := x to x+dim-1 do
    for lj := y+2 to y + dim -1 do
      if (a[li,lj] <> a[li,lj-2])or(a[li,lj]=a[li,lj-1]) then exit;


                          //verifica toate coloanele

  for lj := y to y + dim -1 do
    for li := x+2 to x + dim -1 do
      if (a[li,lj] <> a[li-2,lj])or(a[li,lj]=a[li-1,lj]) then exit;




  patrat := true;

end;


procedure creeaza_b;
var i,j,t:longint;
begin
  for i := 1 to n do
    for j := 1 to m do
      b[i,j] := 0;

  for i := 1 to n do
    for j := 1 to m do
    begin
      if b[i,j] = 0 then
      begin
        d := 1;   v := a[i,j];
        while v= a[i+d,j+d] do inc(d);
        t := 0;
        while d > 0 do
        begin
          inc(t);
          b[i+d-1,j+d-1] := t;
          dec(d);
        end;

      end;
    end;

end;



begin
  assign(input,'sah3.in'); reset(input);
  assign(output,'sah3.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m); cont := n*m;
                                      //bordare
  for i := 0 to m+1 do
  begin
    a[0,i] := -1;
    a[n+1,i] := -1;
  end;
  for i := 0 to n+1 do
  begin
    a[i,0] := -1;
    a[i,m+1] := -1;
  end;

  for i := 1 to n do         //citire
  begin
    for j := 1 to m do
      read(a[i,j]);
    readln();
  end;

  creeaza_b;
  n2:= n-1; m2 := m-1;

  for i := 1 to n2 do
    for j := 1 to m2 do
    begin
      //d := 1;   v := a[i,j];
      //while v= a[i+d,j+d] do inc(d);
      k := 2;    d := b[i,j]; //writeln(d);
      while k <= d do
      begin
        if patrat(i,j,k) then cont := cont+1;
        k := k +1;
      end;

    end;

  write(cont);

  close(input);
  close(output);
end.
