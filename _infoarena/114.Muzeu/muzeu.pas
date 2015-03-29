program Muzeu;

const max=10000;

var n:integer;
    f,fo:text;
    a:array[1..252,1..252]of integer;
    i,j,val,valp:integer;
    c:char;
    msc:boolean;

begin
  assign(f,'muzeu.in'); reset(f);
  readln(f,n);
  for i := 2 to n+1 do
  begin
    a[i,1] := -2;a[i,n+2] := -2; 
    for j := 2 to n+1 do
    begin
      read(f,c);
      case c of
        'P': a[i,j] := 0;
        '.': a[i,j] := max;
        '#': a[i,j] := -2;
      end;
    end;
    readln(f);
  end;
  
  for j := 1 to n+2 do begin a[1,j] := -2;a[n+2,j] := -2; end;
  

  val := 0;valp := 1;
  repeat
    msc:=false;
    for i := 2 to n+1 do
      for j := 2 to n+1 do
      begin
        if a[i,j] = val then
        begin        
          if valp < a[i-1,j] then begin a[i-1,j] := valp; msc := true; end;       
          if valp < a[i+1,j] then begin a[i+1,j] := valp; msc := true; end;       
          if valp < a[i,j-1] then begin a[i,j-1] := valp; msc := true; end;        
          if valp < a[i,j+1] then begin a[i,j+1] := valp; msc := true; end;
        end;
      end;
	val := valp;
	valp := valp + 1;
  until msc = false;

  assign(fo,'muzeu.out'); rewrite(fo);
  for i := 2 to n+1 do
  begin
    for j := 2 to n+1 do
	  if a[i,j] = max then write(fo,'-1 ')
	  else write(fo,a[i,j],' ');
    writeln(fo);
  end;
  close(fo);
end.
