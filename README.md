# Syslog Bağlı Liste Uygulaması

Bu proje, Linux işletim sistemindeki Syslog günlüklerini okuyan ve bu verileri bağlı liste (linked list) veri yapısında tutan basit bir C uygulamasıdır. Uygulama, Syslog dosyasındaki her bir kaydı bir düğüm (node) olarak tutar ve kullanıcıya bu kayıtları ekrana yazdırır.

## Proje Hakkında

Bu projede, Syslog dosyasındaki günlükleri okuma, bunları bağlı liste yapısına ekleme ve ardından bu kayıtları ekrana yazdırma işlemleri yapılmaktadır. Kullanıcı, Syslog kayıtlarını basit bir şekilde takip edebilir ve veri yapılarını öğrenmek amacıyla bağlı listeyi kullanma konusunda deneyim kazanabilir.

## Kullanılan Teknolojiler

- C Programlama Dili
- Bağlı Liste (Linked List) Veri Yapısı

## Kurulum ve Çalıştırma

1. **Kodun İndirilmesi:**

   Bu projeyi GitHub'dan bilgisayarınıza indirerek başlatabilirsiniz:

   ```bash
   git clone https://github.com/your-username/syslog-linked-list.git
   cd syslog-linked-list
   ```

2. **Derleme:**

   C kodunu derlemek için aşağıdaki komutu kullanın:

   ```bash
   gcc -o syslog_linked_list syslog_linked_list.c
   ```

3. **Çalıştırma:**

   Uygulamayı çalıştırmak için aşağıdaki komutu kullanın:

   ```bash
   ./syslog_linked_list
   ```

   Not: Syslog dosyasına erişim için yönetici (root) iznine sahip olmanız gerekebilir. Eğer syslog dosyasına erişim izniniz yoksa, geçici bir test dosyası oluşturabilirsiniz.

## Dosya Yapısı

- `syslog_linked_list.c`: Syslog dosyasını okuyup, verileri bağlı liste yapısında tutan ve ekrana yazdıran ana C dosyası.

## Katkıda Bulunma

Katkıda bulunmak isterseniz, lütfen bir pull request gönderin. Her türlü katkı ve öneri memnuniyetle karşılanır.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakabilirsiniz.
