#ifndef TEXTSTREAM_H
#define TEXTSTREAM_H

#include "ByteStream.h"
#include "CharStream.h"
#include "../Text/Encoding.h"

class TextStream : public CharStream
{
    PIMPL
public:
    TextStream(ByteStream *baseStream, StreamMode mode, Encoding *encoding = &Encoding::UTF8);

    ByteStream &baseStream() const;
    Encoding &codec() const;

    // CharStream interface
public:
    bool canRead() const override final;
    inline bool canSeek() const override final { return false; }
    bool canWrite() const override final;
    bool isClosed() const override final;
    long length() const override final;
    void length(long length) override final;
    long position() const override final;
    CharStream &position(long position) override final;

    void Close() override;
    long Flush() override;
    long Read(CharArray &buffer, long offset, long count) override;
    long ReadLine(CharArray &buffer, long offset) override;
    long Seek(long offset, SeekOrigin origin) override;
    long Write(const CharArray &buffer, long offset, long count) override;
    long WriteLine(const CharArray &buffer, long offset, long count) override;
};

#endif // TEXTSTREAM_H

/*
TextStream gereklilikleri ve Vekil (surrogate) karakter çakışmaları durumunda okuma ve yazma davranışları:

TextStream, karakter verisini binary veriye çevirerek binary stream üzerine yazılmasını sağlar. String ve Binary arasında bağlantı kurar.

-TextStreamMode, TextStream'in akış yönünü belirler. TextStream'in tek yönlü olmasına ihtiyaç vardır çünkü bir binary verinin encoding ile aynı anda okunması ve yazılması,
    istenmeyen bir takım durumlara yol açacaktır. Her şeyden önce, yapılacak encodingin türünü bilmiyoruz. Dolayısıyla karakterlerin de dönüştüğü binary verinin uzunluklarını da
    hesaplayamıyoruz. Bu durum ise TextStream'in aranamaz (cannot seek) olmasına yol açar.
    Yazma ve okuma işlemini aynı kaynak üzerine yapan bir stream (örnek olarak file stream verilebilir) mantıklı olarak araştırılabilir (seekable) olmalıdır. Ancak
    TextStream gibi aynı kaynak üzerine (burada BaseStream) yazan ve okuyan bir stream, araştırılabilir (seekable) değilse, okunan ve yazılan bölgeler birbirini ardışık olarak
    takip edecektir. Yazılan bir veriyi daha sonra dönüp okumak veya okunan bir veriyi daha sonra dönüp değiştirmek imkansızdır. Dolayısıyla çift taraflılık, TextStream için
    gerekli değildir. Her akış yönü için de ayrı kaynaklar tüketildiğinden, TextStream tüketilen kaynakları azaltabilmek adına böyle bir seçim yapılmasını ister. Yoksa
    her iki yön de TextStream için aktif edilebilirdi ancak kişi sadece bir yönü kullanabilirdi ve diğer akış yönü için gereksiz kaynak tüketimleri oluşurdu.

-> Önemli: TextStream, kurucudan aldığı argümanlar (baseStream ve encoding) için yeni yaşam döngüleri oluşturmaz. Eğer nesneler yıkıldıysa, TextStream için de bu nesneler
    yıkılmıştır ve artık okuma / yazma işlemleri gerçekleştirilemez. Hatta owns (CloseHandler) eğer true ise, TextStream'in kaynakları salınamayabilir (Close() çağrılması
    sahip olunmayan belleğe erişim yüzünden hata oluşturur) ve bir takım bellek sızıntıları (memory leaks) meydana gelebilir.

::long ReadLine(CharArray &, long) için, eğer binary kaynaklarda problem yoksa, herhangi bir sorun olmayacaktır. Ancak binary kaynaktaki veri decode edilemiyorsa,
    yerine yer tutucu karakter atanır ve işleme devam edilir. Yeni satır ayıracı veya EndOfStream'e kadar okumaya devam eder. Geri dönüş de okunan karakter sayısını döndürür
    ancak bu boyut end line karakterini kapsamaz.
::long Read(CharArray &, long, long) okuma esnasında ReadLine ile aynı şekilde davranır. Ara karakterler eğer decode edilemiyorsa, yerine yer tutucu karakterler atanır.
    Ancak offset + count indeksi tam olarak UTF16 HighSurrogate üzerine geliyorsa, o karakter metoduno anki çağrılış anında okunmaz. İkinci kez daha uzun bir count seçilirse,
    sorunsuz bir şekilde okuma devam eder. Geri dönüş değeri okunan karakter sayısını verir.
::long WriteLine(const CharArray &, long, long)'ta eğer ara karakterler encode olmuyorsa yerine yer tutucu karakter atanır ve yazma işlemine devam edilir. Eğer ki
    offset + count indeksi bir UTF16 High Surrogate karaktere denk geliyorsa, en sonuna end line atanacağı ve bu karakterin daha sonradan decode edilecek binary veride
    sorun yaratmaması için yerine yer tutucu karakter atanarak yazma işlemi yapılır. Geri dönüş değeri yazılan karakter sayısını verir ve bu end line karakterini içermez.
::long Write(const CharArray &, long, long) Ara karakter eğer encode olmuyorsa, aynı şekilde yerine yer tutucu karakter atanır fakat offset + count indeksi eğer ki bir UTF16 High Surrogate
    karaktere denk gelirse, o karakter yazılmaz. Bir sonraki metot çağırmasında count büyütülerek non-bmp karakterin yazılması sağlanır. Geri dönüş değeri olarak da yazılan karakter
    sayısı verilir.
::long Flush() burada kullanılması gereken bir metottur. Bazı streamler otomatik flush yapabilir ancak TextStream, araya giren bir encoding işlemi barındırdığından ve bazen
    nonbmp karakterler yüzünden çakışmalar yaşanabileceğinden, flush işlemini otomatik hale getirmez. Karakterlerin yazılmasının tamamı bittikten sonra Flush çağrılarak ilgili
    verinin kaynak streame gönderilmesi sağlanır. Geri dönüş değeri olarak da yazılan binary verinin boyutu (byte) döndürülür.
*/
