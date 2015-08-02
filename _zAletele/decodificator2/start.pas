var fin,fout:text;
    a:string;
    i:longint;

begin
assign(fin,'fin.bin');reset(fin);
assign(fout,'fout.bin');rewrite(fout);

read(fin,a);
delete(a,1,8);

repeat
write(fout,pred(a[1]));
write(a[i]);
delete(a,1,9);



until a = '~';

close(fin);
close(fout);
end.

