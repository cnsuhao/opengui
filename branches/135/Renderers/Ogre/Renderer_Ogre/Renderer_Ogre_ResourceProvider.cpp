// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

// -----------------------------------------------------------------------------
// Renderer_Ogre_ResourceProvider.cpp
// -----------------------------------------------------------------------------

#include "OgreArchiveManager.h"
#include "Renderer_Ogre_ResourceProvider.h"

//#include "Ogre.h"


namespace OpenGUI {
	//#####################################################################
	OgreResourceProvider::OgreResourceProvider() {
		mResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	}
	//#####################################################################
	OgreResourceProvider::~OgreResourceProvider() {}
	//#####################################################################
	void OgreResourceProvider::setResourceGroup( const std::string& groupName ) {
		mResourceGroup = groupName;
	}
	//#####################################################################
	std::string OgreResourceProvider::getResourceGroup() const {
		return mResourceGroup;
	}
	//#####################################################################
	void OgreResourceProvider::loadResource( const std::string& filename, Resource& output ) {
		if ( filename.empty() || filename == "" ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "No filename provided", "OgreResourceProvider::loadResource" );
		}

		Ogre::DataStreamPtr dStream =
			Ogre::ResourceGroupManager::getSingleton()
			.openResource(	filename, //resource name
						   mResourceGroup, //resource group
						   false, //search other resource groups?
						   0 ); //ptr to resource object being opened, only needed if searching other groups

		if ( dStream.isNull() ) {
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Ogre::ResourceGroupManager returned bad DataStreamPtr for file: '" + filename + "'", "OgreResourceProvider::loadResource" );
			return; //there is no recovery from this
		}

		size_t rSize = dStream->size();
		if ( rSize ) { // we can do this the easy way!
			output.setSize( rSize );
			dStream->read( output.getData() , rSize );

		} else { //we have to do this the hard way...
			const size_t readSize = 1024;
			typedef std::pair<unsigned char*, size_t> BufferPair;
			typedef std::list<BufferPair> BufferPairList;
			BufferPairList bufferList;
			BufferPair tmpPair;
			unsigned char tmpBuffer[readSize];
			size_t bytesRead;
			size_t totalBytes = 0;

			//build the temp buffer and get the total size
			do {
				bytesRead = dStream->read( tmpBuffer , readSize );
				tmpPair.first = new unsigned char[bytesRead];
				tmpPair.second = bytesRead;
				totalBytes += bytesRead;
				memcpy( tmpPair.first, tmpBuffer, bytesRead );
				bufferList.push_back( tmpPair );
			} while ( !dStream->eof() );

			//write out the read data into a contiguous memory area
			unsigned char* data = new unsigned char[totalBytes];
			bytesRead = 0; //we'll now use this as an offset for writing
			BufferPairList::iterator bplIter = bufferList.begin();
			while ( bplIter != bufferList.end() ) {
				memcpy(( data + bytesRead ), bplIter->first, bplIter->second );
				delete[] bplIter->first; //deallocate as we go
				bytesRead += bplIter->second;
				bplIter++;
			}
			//now we can finally say we're done
			output.setData( data, bytesRead );
		}

	}
	//#####################################################################
	void OgreResourceProvider::unloadResource( Resource& resource ) {
		/*
		Note:
			Is there a reason we need this function in OpenGUI?
			Since the ResourceProvider doesn't create the resource object,
			we have no way to attach extra data to the object which could
			be used to identify it in a meaningful way. As such, there's
			literally nothing to do here other than release the object's data,
			which would happen by itself anyhow. Someone should look into this...
		*/
		resource.release();
	}
	//#####################################################################
}
;//namespace OpenGUI{



