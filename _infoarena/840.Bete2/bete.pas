var a:array[1..3001]of longint;
    n,i,j,valori,k,t,h,max,imax:longint;
    bufin:array[1..65000]of byte;
    ok:boolean;
procedure cauta_binar(u,v,x:longint);
var n,i,m:longint;
begin
  ok := false;

  repeat
    m := ((v-u)div 2)+ u;
    if a[m] = x then
    begin
      ok := true;
      break;
    end
    else
    begin
      if a[m] < x then
      begin
        v := m-1;
      end
      else
      begin
        u := m+1 ;
      end;
    end;


  until u > v;


end;



begin
  assign(input,'bete2.in'); reset(input);
  assign(output,'bete2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); valori := 0;
if n >= 3 then
begin
  for i := 1 to n do readln(a[i]);

  k := 2;

  {repeat                   //metoda 1 sortare
    ok := false;
    for i := 1 to k do
    begin
      if a[i] < a[i+1] then
      begin
        t := a[i];
        a[i] := a[i+1];
        a[i+1] := t;
        ok := true;
      end;
    end;
    k := k-1;
  until ok = false; }

  repeat              //metoda 2 sortare
    max := a[k-1];   imax := k-1;
    for i := k to n do
    begin
      if a[i] > max then
      begin
        max := a[i];
        imax := i;
      end;
    end;

    if imax <> k-1 then
    begin
      t := a[k-1];
      a[k-1] := a[imax];
      a[imax] := t;
    end;

    inc(k);
  until k>n;

  //for i := 1 to n do write(a[i],' ');
  //writeln();

  h:= n-2;

  for i :=  1 to h do
  begin
    for j := i+1 to h+1 do
    begin
      cauta_binar(j+1,n,a[i]-a[j]);
      if ok = true then
      begin
        inc(valori);
      end;
    end;
  end;

  write(valori);
end
else
  write('0');
  close(input);
  close(output);
end.
