const modd=1000000;
var n,i:longint;
    s1,s2,s3,d,t:longint;
    a:array[1..3,1..4]of longint;

procedure invert();inline;
begin
  t := s1; s1 := s2; s2 := s3; s3 := d; d := t;
end;

begin
  readln(n);

  if n <= 3 then write(n)
  else
  begin
    s1 := 1; s2 := 2; s3 := 3; d := 4;
    a[1,1] := 0; a[1,2] := 0; a[1,3] := 1;
    a[2,1] := 0; a[2,2] := 1; a[2,3] := 0;
    a[3,1] := 1; a[3,2] := 1; a[3,3] := 2;
    for i := 4 to n do
    begin
      a[1,d] := a[1,s1];
      a[2,d] := a[1,s2] + a[2,s2];
      a[3,d] := a[1,s3] + a[2,s3] + a[3,s3];

      a[1,d] := a[1,d] mod modd;  //write(a[1,d]);
      a[2,d] := a[2,d] mod modd;  //write(' ',a[2,d]);
      a[3,d] := a[3,d] mod modd;  //writeln(' ',a[3,d]);

      invert();
    end;

    writeln((a[1,s3]+a[2,s3]+a[3,s3])mod modd);

  end;

end.