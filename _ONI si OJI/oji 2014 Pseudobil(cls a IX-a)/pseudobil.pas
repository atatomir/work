var op,n,k,d,dd,i,j,x,y,t,m,cont,nn:longint;
    r:array[0..3005,0..3005]of longint;
    a:array[0..1505,0..1505]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'pseudobil.in'); reset(input);
  assign(output,'pseudobil.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(op);
  readln(n,k,d);

  if op = 1 then
  begin
    if d = 2 then begin writeln(1); exit end;
    dd := (d-3)div 2;
    writeln(d-1+2*(dd*(dd+1)+dd+1));

  end
  else
  begin
    for i := 1 to n do
      for j := 1 to n do
        a[i,j] := 0;

    for i := 0 to n+1 do
    begin
      a[0,i] := -1;
      a[n+1,i] := -1;
      a[i,0] := -1;
      a[i,n+1] := -1;
    end;

    for i := 1 to k do
    begin
      readln(x,y);
      a[x,y] := 1;
    end;


    for t := 1 to n do
    begin
      i := t; j := 1;
      while a[i,j] <> -1 do
      begin
        r[t,n-t+2*j-1] := a[i,j];
        dec(i); inc(j);
      end;
    end;

    for t := 2 to n do
    begin
      i := n; j := t;
      while a[i,j] <> -1 do
      begin
        r[n+t-1,t+2*(j-t+1)-2] := a[i,j];
        dec(i); inc(j);
      end;
    end;

    nn := 2*n-1;
    for i := 0 to nn+1 do
    begin
      r[0,i] := 0;
      r[nn+1,i] := 0;
      r[i,0] := 0;
      r[i,nn+1] := 0;
    end;

    for i := 1 to nn do
      for j := 1 to nn do
        r[i,j] := r[i-1,j] + r[i,j-1] - r[i-1,j-1] + r[i,j];


    readln(m); inc(d);
    for t := 1 to m do
    begin
      readln(x,y);
      i := x; j := y;  cont := 1;      //determinare coord punct
      while a[i+1,j-1] <> -1 do begin inc(i); dec(j); inc(cont); end;
      if j = 1 then
      begin
        x := i;
        y := 2*cont-1 +n-i;
      end
      else
      begin
        x := n-1 + j;
        y := 2*cont-1 + j-1;
      end;

      //calcul raspuns
      writeln(r[x+d-1,y]-r[x-1,y]-r[x+d-1,y-d]+r[x-1,y-d]);

    end;


  end;



  close(input);
  close(output);
end.
