const blc=70000;
      str=70005;
type elem=record
       i,j:longint;
     end;
var a:array[0..255,0..255]of longint;
    c:array[1..62500]of elem;
    i,j,n,ci,cj,x,y:longint;
    bufin,bufout:array[1..65000]of byte;
    chr:char;

procedure add(x,y:longint);
begin
  inc(cj);
  c[cj].i := x; c[cj].j := y;
end;

begin
  assign(input,'muzeu.in'); reset(input);
  assign(output,'muzeu.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n); ci := 1; cj := 0;
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(chr);
      case chr of
        '.': a[i,j] := str;
        '#': a[i,j] := blc;
        'P': begin add(i,j); a[i,j] := 0; end;
      end;
    end;
    readln();
  end;

  for i := 0 to n+1 do
  begin
    a[0,i] := blc;
    a[n+1,i] := blc;
    a[i,0] := blc;
    a[i,n+1] := blc;
  end;

  while ci<=cj do
  begin
    x := c[ci].i; y := c[ci].j; inc(ci);
    if a[x-1,y] = str then begin a[x-1,y] := a[x,y]+1; add(x-1,y); end;
    if a[x+1,y] = str then begin a[x+1,y] := a[x,y]+1; add(x+1,y); end;
    if a[x,y-1] = str then begin a[x,y-1] := a[x,y]+1; add(x,y-1); end;
    if a[x,y+1] = str then begin a[x,y+1] := a[x,y]+1; add(x,y+1); end;
  end;

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      case a[i,j] of
        blc: write('-2 ');
        str: write('-1 ');
      else
        write(a[i,j],' ');
      end;
    end;
    writeln();
  end;


  close(input);
  close(output);
end.

