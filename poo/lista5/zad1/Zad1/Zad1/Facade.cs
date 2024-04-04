using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Mail;
using System.Net;

namespace Zad1
{
    class SmtpFacade
    {
        public void Send(string From, string To,
            string Subject, string Body,
            Stream Attachment, string AttachmentMimeType)
        {
            try
            {
                string smtpServer = "smtp.gmail.com";
                int smtpPort = 587;

                SmtpClient client = new SmtpClient(smtpServer, smtpPort);
                client.EnableSsl = true;
                client.DeliveryMethod = SmtpDeliveryMethod.Network;
                client.UseDefaultCredentials = true;
                //client.Credentials = new NetworkCredential("username", "password");

                MailMessage mailMessage = new MailMessage();
                mailMessage.From = new MailAddress(From);
                mailMessage.To.Add(To);
                mailMessage.Subject = Subject;
                mailMessage.Body = Body;


                if (Attachment != null)
                {
                    Attachment.Position = 0;
                    Attachment mailAttachment = new Attachment(Attachment, AttachmentMimeType);
                    mailMessage.Attachments.Add(mailAttachment);
                }

                client.Send(mailMessage);

                client.Dispose();
                Console.WriteLine("Wiadomość e-mail została wysłana.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Wystąpił błąd podczas wysyłania wiadomości e-mail: " + ex.Message);
            }
        }
    }
}