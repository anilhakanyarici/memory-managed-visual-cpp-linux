#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include "../ByteArray.h"

#ifndef SEEKORIGIN_H
#define SEEKORIGIN_H
enum SeekOrigin { Begin, Current, End };
#endif // SEEKORIGIN_H

#ifndef STREAMMODE_H
#define STREAMMODE_H
enum StreamMode { Read, Write };
#endif // STREAMMODE_H

class ByteStream
{
public:
    virtual bool canRead() const = 0;
    virtual bool canSeek() const = 0;
    virtual bool canWrite() const = 0;
    virtual bool isClosed() const = 0;
    virtual long length() const = 0;
    virtual void length(long length) = 0;
    virtual long position() const = 0;
    virtual ByteStream &position(long position) = 0;

    virtual void Close() = 0;
    inline ByteStream &End() { return this->position(this->length()); }
    virtual long Flush() = 0;
    virtual long Read(ByteArray &buffer, long offset, long count) = 0;
    inline ByteStream &Rewind() { return this->position(0); }
    virtual long Seek(long offset, SeekOrigin origin = SeekOrigin::Begin) = 0;
    virtual long Write(const ByteArray &buffer, long offset, long count) = 0;

    virtual ByteStream &operator <(const ByteArray &buffer);
    virtual long operator >(ByteArray &buffer);
};
#endif // BYTESTREAM_H
/*
Belirlenmiş standartlar ve açıklamalar:

::bool CanRead() const: Stream'in okuma akış yönünün aktif olup olmadığı hakkında bilgi verir. Okuma yönü aktif ise true döner.
    E-> Stream kapatılsa bile metot herhangi bir istisna fırlatmaz ancak geri dönüş değeri false olarak değiştirilebilir.

::bool CanSeek() const: Stream'in araştırılabilir (seekable) olup olmadığını belirler. Araştırılabilir bir stream ise true döner.
    E-> Stream kapatılsa bile metot herhangi bir istisna fırlatmaz ancak geri dönüş değeri false olarak değiştirilebilir.

::bool CanWrite() const: Stream'in yazma akış yönünün aktif olup olmadığı hakkında bilgi verir. Yazma yönü aktif ise true döner.
    E-> Stream kapatılsa bile metot herhangi bir istisna fırlatmaz ancak geri dönüş değeri false olarak değiştirilebilir.

::bool IsClosed() const: Stream'in kapatılıp kapatılmadığına dair bilgi verir.
    E-> Durum ne olursa olsun herhangi bir istisna fırlatmamalıdır.

::long Length() const: Eğer stream araştırılabilir (seekable) ise, stream'in sahip olduğu kaynağın boyutunu (byte) döndürür.
    E-> Eğer stream araştırılabilir (seekable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'in uzunluğuna artık erişilemez.

::void Length(long): Eğer stream araştırılabilir (seekable) ise, stream'in kaynak uzunluğunu değiştirir.
    E-> Eğer stream araştırılabilir (seekable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'in uzunluğuna artık erişilemez.
    E-> Eğer stream index aralığının dışına çıkılmışsa OutOfRange veya ondan türetilmiş bir istisna fırlatmalıdır.

::long Position() const: Eğer stream araştırılabilir (seekable) ise, stream'in o anki okuma veya yazma yapacağı indeks değerini döndürür.
    E-> Eğer stream araştırılabilir (seekable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'in indeksleri artık bilinemez.

::ByteStream Position(long): Eğer stream araştırılabilir (seekable) ise, stream'in o anki okuma veya yazma yapacağı indeks değerini değiştirir. Geri dönüş değeri olarak da
    stream'in referans değeri döndürülür. Bunun sebebi de tek satırda hem pozisyon değiştirilip hem de stream ile işlem yapılmasını sağlamaktır.
    E-> Eğer stream araştırılabilir (seekable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'in indeksleri artık bilinemez.
    E-> Eğer stream index aralığının dışına çıkılmışsa OutOfRange veya ondan türetilmiş bir istisna fırlatmalıdır.

::void Close(): Eğer stream yazılabilir ise bellekteki veri akıtılır (flush) ve stream kaynakları salınır.
    E-> Herhangi bir istisna fırlatmaz. Bunun açık sebebi, bir stream'in başka kabuk stream'ler veya tek yönlü ve çok fonksiyonlu girdi çıktı işlemleri yapabilen
    bir takım sınıflar içinde kullanılabilmesi durumlarından kaynaklı olarak iç stream'in kapatılması yüzünden kabuk stream'in kaynaklarının salınması esnasında
    iç stream yüzünden oluşabilecek gereksiz bir istisna fırlatma durumunun önüne geçilmiş olmasıdır.

::ByteStream &End(): Stream'in pozisyonunu en sona getirir.
    E-> Gövde kısımda Position(long) ve Length(void) metotları çağrıldığından bu metotların fırlatacağı istisnalar meydana gelebilir.

::long Flush(): Tamponda biriktirilen veriyi ilgili kaynağa akıtır. Ancak stream yazılabilir ise kullanılabilir.
    E-> Eğer stream yazılabilir (writable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Kaynağı salınmış bir stream, yazma işlemi gerçekleştiremez.

::long Read(ByteArray &, long, long): Stream posizyonundan başlayarak kaynaktaki verileri okur ve buffer argümanına belirlenen offsetten başlayarak yazar. ByteArray
    sınıfının kaynakları kolayca genişletilebilir. Eğer ki istenen sayıda veri bu diziye yazılamayacak kadar büyükse, stream otomatik olarak bu dizinin kaynağını genişletir.
    Bunun başlıca sebebi, kodlama esnasında yazımı kolaylaştırmak ve bazı durumlarda karşılaşılan okunacak verinin boyutunun bilinmemesi yüzünden yapılacak kontrolleri azaltmaktır.
    Geri dönüş değeri de stream üzerinden ne kadar veri okunduğunu içerir. Eğer okumanın sonuna gelindiyse (EOF/EndOfStream) 0 değeri döndürmelidir. Okuma sonları
    herhangi bir istisna fırlatmamalıdır. Eğer stream'in kaynakları artık kullanılabilir değilse veya bir I/O beklemesi veri gelmeden kesilmişse -1 değeri döndürmelidir.
    E-> Eğer stream okunabilir (readable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü artık okunacak kaynak kalmamıştır.
    E-> Dizi her ne kadar genişletilebilir olsa da, offset değeri dizinin uzunluğundan fazla olamaz. Bunun nedeni herhangi bir hatalı kodlamada oluşabilecek bellek şişmesini önlemektir.
    Dolayısıyla offset eğer buffer'ın uzunluğundan büyükse, offset 0'dan küçükse veya count 0'dan küçükse OutOfRange veya ondan türetilmiş bir istisna fırlatılmalıdır.

::ByteStream Rewind(): Stream'in pozisyonunu en başa getirir.
    E-> Gövde kısımda Position(long) ve Length(void) metotları çağrıldığından bu metotların fırlatacağı istisnalar meydana gelebilir.

::long Seek(long, SeekOrigin): Araştırma orijinine (SeekOrigin) bağlı olarak stream'in pozisyonunu ayarlar. Geri dönüş değeri de yeni pozisyon değerini verir.
    E-> Eğer stream araştırılabilir (seekable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'in indeksleri artık bilinemez.
    E-> Eğer stream index aralığının dışına çıkılmışsa OutOfRange veya ondan türetilmiş bir istisna fırlatmalıdır.

::long Write(const ByteArray &, long, long): Buffer argümanında belirlenen offsetten başlayarak okur ve Stream posizyonundan başlayarak stream kaynaklarına yazar. Geri dönüş değeri olarak
    yazılan verinin boyutu döndürülür. Eğer stream kesilmişse veya içerideki kaynaklar salınmışsa -1 döndürür.
    E-> Eğer stream yazılabilir (writable) değilse, NotSupportedException veya ondan türetilmiş bir istisna fırlatmalıdır.
    E-> Eğer stream kapatılmış ise, ObjectClosedException veya ondan türetilen bir istisna fırlatılmalıdır. Çünkü kaynakları salınmış bir stream'e yazma yapılamaz.
    E-> Eğer offset ve count değerinin belirlediği veri kümesi buffer'ın bir alt kümesi değilse OutOfRange veya ondan türetilmiş bir istisna fırlatmalıdır.

::ByteStream &operator <(const ByteArray &): ::long Write(const ByteArray &, long, long) metodunu çağırarak tüm buffer verisini stream kaynağına yazar. Geri dönüş olarak
    stream'in referans değerini döndürür. Böylece tek satırda birden fazla yazma işlemi gerçekleştirilebilir.
    E-> Write metodundan kaynaklı istisnalar oluşabilir.

::long &operator >(ByteArray &): ::long Read(ByteArray &, long, long) metodunu çağırarak kaynaktan veri okur. Buffer'ın giriş uzunluğu önemli değildir. Read metodu sayesinde
    boyutu yetersiz buffer genişletilecektir. Okunan veriyi de bufferın en başından itibaren yazmaya başlar. Offset'e otomatik olarak 0 atanır.
    E-> Read metodundan kaynaklı istisnalar oluşabilir.
*/
