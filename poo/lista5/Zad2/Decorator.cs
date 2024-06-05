using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.IO;

namespace Zad2
{
    public class CaesarStream : Stream
    {
        private Stream stream;
        private int shift;

        public CaesarStream(Stream stream, int shift)
        {
            this.stream = stream;
            this.shift = shift;
        }

        public override bool CanRead => stream.CanRead;
        public override bool CanSeek => stream.CanSeek;
        public override bool CanWrite => stream.CanWrite;
        public override long Length => stream.Length;

        public override long Position
        {
            get => stream.Position;
            set => stream.Position = value;
        }

        public override void Flush()
        {
            stream.Flush();
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            int bytesRead = stream.Read(buffer, offset, count);
            for (int i = offset; i < offset + bytesRead; i++)
            {
                buffer[i] = Encrypt(buffer[i]);
            }
            return bytesRead;
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            byte[] encryptedBuffer = new byte[count];
            for (int i = offset; i < offset + count; i++)
            {
                encryptedBuffer[i - offset] = Encrypt(buffer[i]);
            }
            stream.Write(encryptedBuffer, 0, count);
        }

        private byte Encrypt(byte value)
        {
            return (byte)((value + shift) % 256);
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            return stream.Seek(offset, origin);
        }

        public override void SetLength(long value)
        {
            stream.SetLength(value);
        }
    }
}
