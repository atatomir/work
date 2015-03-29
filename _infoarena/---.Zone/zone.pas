var l1,l2,c1,c2,i,j,n:longint;
    a:array[0..550,0..550]of int64;
    bufin:array[1..65000]of byte;
    s,ss,s2:array[1..9]of int64;
    ok:boolean;

function verif(x:int64):boolean;
var i:longint;
begin
  verif := false;
  for i := 1 to 9 do
    if s[i] = x then
    begin
      verif := true;
      exit;
    end;
end;

begin
  assign(input,'zone.in'); reset(input);
  assign(output,'zone.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to 9 do read(s[i]); readln();
  for i := 1 to n do
  begin
    for j := 1 to n do
      read(a[i,j]);
    readln();
  end;
  for i := 2 to n do
  begin
    a[1,i] := a[1,i-1] + a[1,i];
    a[i,1] := a[i-1,1] + a[i,1];
  end;
  for i := 2 to n do
    for j := 2 to n do
      a[i,j] := a[i-1,j] + a[i,j-1] - a[i-1,j-1] + a[i,j];


  for l1 := 1 to n-2 do
    for c1 := 1 to n-2 do
      if verif(a[l1,c1]) then
        for c2 := c1+1 to n-1 do
          if verif(a[l1,c2] - a[l1,c1]) and verif(a[l1,n]-a[l1,c2]) then
            for l2 := l1+1 to n-1 do
            begin
              ss[1] := a[l1,c1];
              ss[2] := a[l1,c2] - a[l1,c1];
              ss[3] := a[l1,n] - a[l1,c2];
              ss[4] := a[l2,c1] - a[l1,c1];
              ss[5] := a[l2,c2] - a[l1,c2] - a[l2,c1] + a[l1,c1];
              ss[6] := a[l2,n] - a[l1,n] - a[l2,c2] + a[l1,c2];
              ss[7] := a[n,c1] - a[l2,c1];
              ss[8] := a[n,c2] - a[n,c1] - a[l2,c2] + a[l2,c1];
              ss[9] := a[n,n] - a[n,c2] - a[l2,n] + a[l2,c2];

              //for i := 1 to 9 do writeln(ss[i]); writeln();

              for i := 1 to 9 do s2[i] := s[i];

              ok := true;
              for i := 1 to 9 do
                if not verif(ss[i]) then ok := false;

              if ok then
              begin
                writeln(l1,' ',l2,' ',c1,' ',c2);
                close(output);
                exit;
              end
              else
                for i := 1 to 9 do
                  s[i] := s2[i];

            end;



  close(input);
  close(output);
end.
