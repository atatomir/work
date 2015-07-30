var p,m,n,i,j:longint;
    gm,gn:longint;
    a,b:array[1..20003]of smallint;
    bufin:array[1..65000]of byte;
    g:array[1..2001,1..2001]of boolean;


begin
  assign(input,'bile.in'); reset(input);
  assign(output,'bile.out'); rewrite(output);
  settextbuf(input,bufin);
  readln(m,n,p);
  for i := 1 to m do                   //initializare
    for j := 1 to m do g[i,j] := false;

  for i := 1 to p do                 //citire obstacole
  begin
    readln(gm,gn);
    g[gm,gn] := true;
  end;
  for i := 1 to n do readln(a[i]);       //citire prima linie

  for i := 2 to m do
  begin
    for j := 1 to n do
    begin
      if g[i-1,j]  then
      begin
        b[j-1] := b[j-1] + (a[j]+1)div 2;     //cu obstacol
        b[j+1] := b[j+1] + (a[j])div 2;
        b[j] := 0;
      end
      else
      begin
        b[j] := b[j] + a[j];        //fara obstacol
      end;
    end;

    for j := 1 to n do
    begin
      a[j] := b[j];
      b[j] := 0;
      //write(a[j],'_');    //debug
    end;
    //writeln();  //debug

  end;

  for i := 1 to n do writeln(a[i]);

  close(input);
  close(output);
end.
