program lungimi;

type
  seg=record
    a,b:longint;
  end;

var f,fo:text;
    n,j,k,imin:smallint;
    t,i:byte;
    a,b,a2,b2,s:longint;

    lg:array[1..5000]of seg;
    schimb :boolean;
    ta:seg;
    bufin,bufout:array[1..65000]of byte;


begin
  assign(f,'linterv.in'); reset(f);
  settextbuf(f,bufin);
  assign(fo,'linterv.out'); rewrite(fo);
  settextbuf(fo,bufout);
  readln(f,t);
  for i := 1 to t do
  begin
    s:=0;
    readln(f,n);
    for j := 1 to n do readln(f,lg[j].a,lg[j].b);
    k := 1;
    for j := 1 to n-1 do begin
      imin := j;
      for k := j + 1 to n do
      begin
        if lg[k].a < lg[imin].a then imin := k;
      end;
      if imin <> j then
      begin
        ta := lg[j];
        lg[j]:= lg[imin];
        lg[imin] := ta;

      end;
    end;

    {
    k := n -1;
    repeat                 //ordonare
      schimb:=false;
      for j := 1 to k do
        if lg[j].a > lg[j+1].a then
        begin
          ta := lg[j];
          lg[j] := lg[j+1];
          lg[j+1] := ta;
          schimb := true;
        end;
      k := k - 1;
    until schimb=false;   //eordonare
    }
{    a := lg[1].a; b := lg[1].b;
    for j := 2 to n do
    begin
      a2:=lg[j].a;
      b2:=lg[j].b;
      if a2 <= b then
      begin
        if b2 >= b then b := b2 ;
      end
      else
      begin
        s := s + b-a;
        a:=a2;
        b:=b2;
      end;
    end;
    s := s + b-a;
 }   writeln(fo,s);
  end;
  close(f); close(fo);
end.
